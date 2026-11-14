---
name: spec-change-review
runs_on: host
verifies: "Requirement changes are reviewed against the code and checks they govern."
description: "Check skill. Requirement changes are reviewed against the code and checks they govern. Run when a requirement names this skill in its Verified by line or a change touches what it checks."
---

# Skill: spec-change-review

**What it verifies**: Requirement changes are reviewed against the code and checks they govern.

## How to run

From this repo, with `ABSTRACTX_PATH` set:

```bash
python3 "$ABSTRACTX_PATH/tools/spectrace_matrix.py" --root . --changes --prompt
python3 "$ABSTRACTX_PATH/tools/spectrace_matrix.py" --root . --check-drift
python3 "$ABSTRACTX_PATH/tools/spectrace_matrix.py" --root . --check-skills
python3 "$ABSTRACTX_PATH/tools/spectrace_matrix.py" --root . --matrix
```

Read each changed requirement in the review bundle and say which `Verified by` skills must be re-run.

## Pass criteria

Drift 0, skill problems 0, no BROKEN requirement, and every changed requirement reviewed.

## Evidence

The command and its output in the commit message.
