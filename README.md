# abstractx-pico2-offload

Firmware for a Raspberry Pi Pico 2 or Pico 2 W (RP2350) used as the motor and RC I/O companion of a Linux
flight computer (Radxa Cubie A5E or A7A). It does four jobs on the RP2350's PIO:

1. DShot motor outputs
2. ESC serial passthrough on the motor pins (configuration and firmware update), only while disarmed
3. NeoPixel status LEDs
4. Six channels of RC receiver PWM decode

The flight computer talks to it over a 5-wire Dual-SPI link (SCLK, CS_N, IO0, IO1, INT_REQ) with AbstractX's
64-byte TLPs, the same TLPs it would send a Tang FPGA running `abstractx-fpga`. Wi-Fi is never started.

It is one project in the [`flight`](https://github.com/tcmichals/flight) workspace, which pins the versions that
work together and passes in AbstractX and pio2. Requirements: [docs/SPECIFICATION.md](docs/SPECIFICATION.md).

## Status

Specification only. No firmware yet; nothing has run on hardware. See [TODO.md](TODO.md).
