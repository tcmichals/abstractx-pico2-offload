# @impl [SPEC-OFFLOAD-07] docs/SPECIFICATION.md (firmware build: Pico SDK, AbstractX passed in, no Wi-Fi code)
cmake_minimum_required(VERSION 3.21)

# @impl [SPEC-OFFLOAD-06] docs/SPECIFICATION.md (AbstractX is passed in, never searched for by path)
if(NOT DEFINED ABSTRACTX_PATH AND DEFINED ENV{ABSTRACTX_PATH})
    set(ABSTRACTX_PATH "$ENV{ABSTRACTX_PATH}")
endif()
if(NOT DEFINED ABSTRACTX_PATH OR NOT EXISTS "${ABSTRACTX_PATH}/include/asp_tlp64.hpp")
    message(FATAL_ERROR "Set ABSTRACTX_PATH to an AbstractX checkout (the flight workspace passes it in).")
endif()
set(ABSTRACTX_PATH "${ABSTRACTX_PATH}" CACHE PATH "AbstractX checkout")

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "${ABSTRACTX_PATH}/cmake/toolchains/arm-none-eabi.cmake")
endif()

if(NOT DEFINED PICO_SDK_PATH)
    if(DEFINED ENV{PICO_SDK_PATH})
        set(PICO_SDK_PATH "$ENV{PICO_SDK_PATH}")
    else()
        set(PICO_SDK_PATH "$ENV{HOME}/.tools/pico-sdk")
    endif()
endif()
set(PICO_SDK_PATH "${PICO_SDK_PATH}" CACHE PATH "Pico SDK")
set(PICO_PLATFORM "rp2350-arm-s" CACHE STRING "RP2350, Arm cores, secure")
set(PICO_BOARD "pico2_w" CACHE STRING "pico2_w or pico2")
include("${PICO_SDK_PATH}/external/pico_sdk_import.cmake")

project(abstractx_pico2_offload C CXX ASM)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# AbstractX as a subproject. Its RP2350 target calls pico_sdk_init(); EXCLUDE_FROM_ALL builds only what
# this firmware links (abstractx_core), never the Wi-Fi target.
set(ABSTRACTX_TARGET "pico2w" CACHE STRING "AbstractX target")
add_subdirectory("${ABSTRACTX_PATH}" abstractx EXCLUDE_FROM_ALL)
if(NOT COMMAND pico_add_extra_outputs)
    message(FATAL_ERROR "Pico SDK not initialised; check PICO_SDK_PATH (${PICO_SDK_PATH}).")
endif()

add_executable(abstractx_pico2_offload src/main.cpp)
target_compile_options(abstractx_pico2_offload PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions -fno-rtti -Wall -Wextra>)
# Not abstractx_target_pico2w: it starts Wi-Fi on Core 0 (AbstractX [SPEC-PICO-CORE-01]).
target_link_libraries(abstractx_pico2_offload PRIVATE
    abstractx_core
    pico_stdlib
)
pico_enable_stdio_usb(abstractx_pico2_offload 1)
pico_enable_stdio_uart(abstractx_pico2_offload 0)
# AbstractX's toolchain file does not set the .elf suffix picotool needs (as in AbstractX's own Pico apps).
set_target_properties(abstractx_pico2_offload PROPERTIES SUFFIX ".elf")
pico_add_extra_outputs(abstractx_pico2_offload)
