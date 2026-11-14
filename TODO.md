# TODO

- [x] Build: CMake with the Pico SDK for `pico2` / `pico2_w`, taking `ABSTRACTX_PATH` ([SPEC-OFFLOAD-07]).
- [ ] AbstractX: an RP2350 target without Wi-Fi, so the HAL can be used here ([SPEC-OFFLOAD-07]).
- [ ] Take `PIO2_PATH` once the first `pio2` program is built.
- [ ] Move ESC passthrough, 4-way and MSP from `rt-fc-offloader/firmware` ([SPEC-OFFLOAD-06]); check RP2040 code on the RP2350.
- [ ] Compare `rt-fc-offloader`'s `dshot.pio` / `esc_pio_uart.pio` (ran on hardware) with `pio2`'s `dshot_bidir.pio` / `esc_serial.pio`; keep `pio2`'s.
- [ ] NeoPixel and 6-channel PWM-decode programs in `pio2`.
- [ ] Count the PIO state-machine budget ([SPEC-OFFLOAD-01]).
- [ ] SPI target on PIO with the exchange, dummy bytes and IO1 status ([SPEC-OFFLOAD-02], [SPEC-OFFLOAD-03]).
- [ ] `INT_REQ` level and queue ([SPEC-OFFLOAD-04]).
- [ ] Watchdog timeout and passthrough lockout ([SPEC-OFFLOAD-05]).
- [ ] Bench on the Pico 2 W: CRC-error sweep over SCLK, scope the turnaround and CS-high time.
- [ ] Proposal, not decided: USB MSP / 4-way straight to `python-imgui-esc-configurator` for ESC setup without the SBC.
- [ ] Write the skills' commands once there is a build and tests.
