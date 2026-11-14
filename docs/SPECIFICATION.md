# abstractx-pico2-offload specification

Decided by the owner on 2026-11-13, with `flight` [SPEC-FLIGHT-11] and [SPEC-FLIGHT-12].

### `[SPEC-OFFLOAD-01]` Four Jobs on a Pico 2, Wi-Fi Off
* **Requirement**: the firmware runs on a Pico 2 or Pico 2 W (RP2350) and does four jobs on the chip's own PIO:
  DShot motor outputs; ESC serial passthrough on the motor pins; NeoPixel status LEDs; six channels of RC receiver PWM decode.
  On the Pico 2 W the wireless chip is never started, and its pins and PIO block stay unused.
* **Why**: replaces the Gowin FPGA companion on the Cubie A5E and A7A: faster to start and cheaper, and the RP2350 runs PIO programs natively.
* **Verified by**: `board-bringup`
* **Implementation Target**: `src/`
* **Not implemented yet**: no firmware. The PIO state-machine budget for all four jobs plus the link has not been counted against the real programs.

### `[SPEC-OFFLOAD-02]` Dual-SPI Exchange with Turnaround Bytes
* **Requirement**: the RP2350 is the SPI target on PIO, on SCLK, CS_N, IO0, IO1, with an `INT_REQ` output. An exchange inside one CS is:
  1. a command byte, one bit per clock on IO0, host driving; during it the Pico drives a status byte on IO1 (replies queued; flags for serial data, reply ready, fault);
  2. a 64-byte request TLP, two bits per clock, host driving;
  3. two dummy bytes, one bit per clock, IO0 and IO1 driven by neither side;
  4. a 64-byte reply TLP, two bits per clock, Pico driving.
  Requests and replies are AbstractX 64-byte TLPs with the CRC32 footer. Channels separate registers, serial and events; a reply carries the tag of the request it answers.
  A Tang board running `abstractx-fpga` must accept the same exchange, so either companion fits the same host.
* **Why**: the dummy bytes cover the direction change on IO0/IO1 and the command decode; the status byte tells the host what is waiting before the reply arrives.
* **Verified by**: `host-tests`, `board-bringup`
* **Implementation Target**: `src/`
* **Not implemented yet**: no code. The link has no single owner yet (AbstractX's `TLP_BUS_SPECIFICATION.md` is the likely one); once named, this requirement points there instead of restating it. Command byte values are not chosen. `abstractx-fpga` does not implement the exchange.

### `[SPEC-OFFLOAD-03]` No CPU Work Inside a Transaction
* **Requirement**: the reply TLP is staged by DMA before CS falls: the answer to an earlier request, or the latest snapshot (RC PWM values, status). The CPU handles the request after CS rises, stages the next reply and re-arms both DMAs. Command decode inside the turnaround is done by PIO.
* **Why**: CPU latency on the RP2350 (interrupts, flash cache misses, USB) is not bounded tightly enough to fit inside two dummy bytes at 10–20 MHz.
* **Verified by**: `host-tests`, `board-bringup`
* **Implementation Target**: `src/`
* **Not implemented yet**: no code; the minimum CS-high time between transactions is not measured.

### `[SPEC-OFFLOAD-04]` INT_REQ Is a Level
* **Requirement**: `INT_REQ` is high while any reply or event is queued and low when the queue is empty. It is not raised for each PWM edge; RC PWM values ride in every reply. It is raised for a PWM signal loss.
* **Why**: a level cannot be missed as an edge can; the 1 kHz flight loop reads PWM from every reply without interrupts.
* **Verified by**: `host-tests`, `board-bringup`
* **Implementation Target**: `src/`
* **Not implemented yet**: no code.

### `[SPEC-OFFLOAD-05]` Passthrough Only While Disarmed; Link Watchdog Stops the Motors
* **Requirement**: ESC serial passthrough is refused while armed. While passthrough runs on a motor pin, DShot is off on that pin. ESC serial is buffered both ways and the status reports bytes waiting and free space.
  When no exchange with a good CRC arrives within the watchdog timeout, the Pico sends DShot 0 to every motor and refuses passthrough.
* **Why**: a motor must never spin from a stale command or while its line is a serial port.
* **Verified by**: `host-tests`, `board-bringup`
* **Implementation Target**: `src/`
* **Not implemented yet**: no code. The watchdog timeout is not chosen.

### `[SPEC-OFFLOAD-06]` Owners Elsewhere, No Copies
* **Requirement**: TLP format and the RP2350 target come from AbstractX (`targets/pico2w_rp2350`); PIO programs come from `pio2`. Both are passed in by the `flight` workspace (`ABSTRACTX_PATH`, `PIO2_PATH`), never found by `../` paths and never copied.
  The ESC passthrough, 4-way and MSP code that ran on hardware in `rt-fc-offloader/firmware` moves here, and that copy is retired.
* **Why**: `flight` [SPEC-FLIGHT-01] and [SPEC-FLIGHT-05]: one owner per block.
* **Verified by**: `spec-change-review`
* **Implementation Target**: `CMakeLists.txt`
* **Not implemented yet**: no build; the move from `rt-fc-offloader` has not started.
