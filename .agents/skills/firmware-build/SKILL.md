---
name: firmware-build
runs_on: host
verifies: "The firmware configures and builds for pico2_w and pico2, and the ELF holds no Wi-Fi code."
description: "Check skill. The firmware configures and builds for pico2_w and pico2, and the ELF holds no Wi-Fi code. Run when a requirement names this skill in its Verified by line or a change touches the build or src/."
---

# Skill: firmware-build

**What it verifies**: [SPEC-OFFLOAD-07]: both board presets configure and build, and the linked ELF contains no `cyw43_` symbol.

## How to run

From this repo, with `ABSTRACTX_PATH` set to the workspace's AbstractX checkout (its `third_party/etl` initialised):

```bash
for p in pico2_w pico2; do
  cmake --preset $p && cmake --build --preset $p -j || exit 1
  elf=build/$p/abstractx_pico2_offload.elf
  test -s "$elf" && test -s build/$p/abstractx_pico2_offload.uf2 || { echo "FAIL: no ELF/UF2 for $p"; exit 1; }
  syms=$(arm-none-eabi-nm "$elf") || exit 1
  if grep -q ' cyw43_' <<<"$syms"; then echo "FAIL: Wi-Fi code in $elf"; exit 1; fi
  arm-none-eabi-size "$elf"
done
```

`arm-none-eabi-nm` / `-size` are next to the compiler AbstractX's toolchain file finds (`~/.tools/...`).

## Pass criteria

Both presets build, both `.elf` and `.uf2` files are non-empty, `nm` succeeds and finds no `cyw43_` symbol in either ELF. A missing ELF is a failure, never a pass.

## Evidence

The `arm-none-eabi-size` lines and the `nm` result in the commit message.
