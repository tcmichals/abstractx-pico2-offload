---
name: host-tests
runs_on: host
verifies: "Firmware logic built and tested on the host: link framing, exchange state machine, watchdog, passthrough lockout."
description: "Check skill. Firmware logic built and tested on the host: link framing, exchange state machine, watchdog, passthrough lockout. Run when a requirement names this skill in its Verified by line or a change touches what it checks."
---

# Skill: host-tests

**What it verifies**: Firmware logic built and tested on the host: link framing, exchange state machine, watchdog, passthrough lockout.

## How to run

Not defined yet: there is no build. Defined with the first code ([SPEC-OFFLOAD-02]).

## Pass criteria

Every test passes; a test that cannot fail is not evidence.

## Evidence

The command and its output in the commit message.
