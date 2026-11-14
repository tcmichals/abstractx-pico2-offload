// @impl [SPEC-OFFLOAD-07] docs/SPECIFICATION.md (firmware entry; no Wi-Fi, links abstractx_core only)
#include <cstdio>

#include "asp_tlp64.hpp"
#include "pico/stdlib.h"

// The link carries AbstractX's 64-byte TLPs ([SPEC-OFFLOAD-02]).
static_assert(sizeof(abstractx::Tlp64) == 64, "link frames are 64-byte TLPs");

int main() {
    stdio_init_all();
    std::printf("abstractx-pico2-offload: no jobs yet\n");
    while (true) {
        tight_loop_contents();
    }
}
