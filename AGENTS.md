# Instructions for AI assistants and contributors

abstractx-pico2-offload follows AbstractX's SpecTrace (AbstractX `AGENTS.md` section 0, `docs/SPECTRACE.md`).

1. **Spec first.** Requirements live in `docs/SPECIFICATION.md` as ``### `[SPEC-OFFLOAD-NN]` Title`` blocks with
   `* **Requirement**:`, `* **Why**:`, `* **Verified by**:` (skill names from `.agents/skills/`) and
   `* **Implementation Target**:` lines. Change the requirement before the code.
2. **Tags in code.** Implementing code carries `// @impl [SPEC-*] <spec file>`; tests carry `@verifies [SPEC-*] <spec file>`
   and must call the code the tag names.
3. **Check with the skills** named in `Verified by` (`.agents/skills/<name>/SKILL.md`; Claude Code reads them through
   `.claude/skills`). SpecTrace runs from an AbstractX checkout given by `ABSTRACTX_PATH`:
   ```bash
   python3 "$ABSTRACTX_PATH/tools/spectrace_matrix.py" --root . --check-skills
   python3 "$ABSTRACTX_PATH/tools/spectrace_matrix.py" --root . --check-drift
   python3 "$ABSTRACTX_PATH/tools/spectrace_matrix.py" --root . --check-verifies
   python3 "$ABSTRACTX_PATH/tools/spectrace_matrix.py" --root . --matrix     # look for BROKEN
   ```
4. **Record results and lessons.** Commands and their output go in the commit message; every lesson goes in
   `engineering_log.md` with a category (`product-bug`, `tool-bug`, `false-alarm`, `process-gap`, `hardware-fact`).
   A fix comes with a test that fails on the old code.
5. **No sibling paths.** Dependencies (AbstractX, pio2) are passed in by the `flight` workspace (`ABSTRACTX_PATH`,
   `PIO2_PATH`); never `../` paths or copies ([SPEC-OFFLOAD-06]).
6. **Safety.** Motor tests run with props off. Never weaken the link watchdog or the passthrough lockout to make a test pass.
7. **Never claim done without evidence**; end every report with what was not checked (target, hardware, tool).
8. **Git.** Commits use `Tim Michals <tcmichals@gmail.com>` and carry no `Co-Authored-By` or other AI metadata.
   Licence: GPL-3.0-or-later.
