# abstractx-pico2-offload Engineering Log

Lessons, each with a category: `product-bug`, `tool-bug`, `false-alarm`, `process-gap` or `hardware-fact`. Format as in AbstractX's `engineering_log.md`.

## 2026-11-13: The Wi-Fi check passed when there was no ELF

* **Category**: `tool-bug`
* **Symptom**: the first `firmware-build` run printed "no cyw43_ symbols" for both boards, but neither build had produced an ELF, and an empty `.uf2` passed `test -f`.
* **Cause**: `arm-none-eabi-nm` failed on the missing file, and `grep -q` on its empty output found nothing, which the script read as a pass.
* **Fix**: the skill requires a non-empty ELF and UF2 and stops if `nm` fails. Shown both ways: this build passes (0 `cyw43_` symbols); a scratch copy linking `pico_cyw43_arch_none` and calling `cyw43_arch_init()` fails (24 `cyw43_` symbols).

## 2026-11-13: AbstractX as a subproject built its Wi-Fi target too

* **Category**: `product-bug`
* **Symptom**: no ELF on either board. On `pico2`, AbstractX's `targets/pico2w_rp2350/src/hal_platform.cpp` failed: `pico/cyw43_arch.h: No such file or directory`. The firmware does not link that target.
* **Cause**: `add_subdirectory` builds every target in AbstractX by default, including `abstractx_target_pico2w`, which needs the CYW43 headers and starts Wi-Fi (AbstractX [SPEC-PICO-CORE-01]).
* **Fix**: AbstractX is added with `EXCLUDE_FROM_ALL`, so only `abstractx_core` is built. AbstractX still has no RP2350 target without Wi-Fi (`TODO.md`).
* **Which check should have caught it**: `firmware-build` on both boards; it did, once the false pass above was fixed.
