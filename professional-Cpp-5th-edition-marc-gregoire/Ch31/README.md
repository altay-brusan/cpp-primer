# Chapter 31 — Conquering Debugging

> **Topic:** Planning for bugs (error logging, debug traces, ring buffers,
> assertions), recognizing memory-error categories, and a step-by-step
> debugging walkthrough.

## Samples

| # | Folder | What it demonstrates |
|---|--------|----------------------|
| 01 | `01_StartTimeDebugMode` | Debug tracing toggled at startup via a `-d` flag through a variadic `Logger`. |
| 02 | `02_CompileTimeDebugMode` | The same logging selected at compile time with `DEBUG_MODE`/`#ifdef` (a no-op in release). |
| 03 | `03_RingBuffer` | A fixed-size circular trace buffer that keeps only the most recent entries. |
| 04 | `04_Assertions` | `assert()` usage, custom-message/always-fail idioms, and the `NDEBUG` caveat. |
| 05 | `05_MemoryErrors` | A catalog of memory-freeing/access error categories (intentional UB). |
| 06 | `06_ArticleCitations` | A worked debugging example in five stages: buggy → `println` traces → stream-state traces → stream fix → final debugged version. |

## Build & run

```powershell
./run.ps1 -Chapter 31           # interactive: pick a sample, build & run
./run.ps1 -Verify -Chapter 31   # compile-check every sample (no run)
```

## Notes

- **Self-contained programs:** `01_StartTimeDebugMode`, `02_CompileTimeDebugMode`,
  `04_Assertions` (intentionally aborts on the second assert).
- **Intentional-bug demo:** `05_MemoryErrors` compiles but deliberately performs
  undefined behavior — it may crash or corrupt memory if run.
- **ArticleCitations example:** each stage links its folder's `ArticleCitations.cpp`,
  reads a filename from stdin, and needs `paper1.txt`/`paper2.txt` (provided in
  `06_ArticleCitations/`). Stages 01–04 are intentional-bug stages (wrong/blank output
  or a crash on `paper2.txt`); stage 05 is the fixed version.
