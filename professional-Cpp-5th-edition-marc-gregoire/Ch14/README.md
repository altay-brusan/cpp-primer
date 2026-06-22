# Chapter 14 — Handling Errors

> **Topic:** Throwing and catching exceptions — the standard exception
> hierarchy and polymorphic catching, custom exception classes, `noexcept`,
> rethrowing, stack unwinding with RAII, `source_location`, `stacktrace`,
> allocation failures, and errors in constructors.

## Samples

| # | Folder | What it demonstrates |
|---|--------|----------------------|
| 01 | `01_ReadIntegerFile` | One `readIntegerFile` example evolving across 11 files: from no error handling → throwing/catching ints, `const char*`, and exception objects → catch-by-value vs reference → multiple/any handlers → a custom `set_terminate` handler. |
| 02 | `02_noexcept` | The `noexcept` specifier vs the `noexcept(expr)` operator. |
| 03 | `03_ExceptionsAndPolymorphism` | Descriptive `what()` messages, catching derived exceptions by base reference, correct vs incorrect catch ordering, and writing a `FileError` hierarchy. |
| 04 | `04_NestedException` | `throw_with_nested` / `rethrow_if_nested`. |
| 05 | `05_Rethrow` | Rethrowing with bare `throw;` and why it avoids the slicing `throw e;` causes. |
| 06 | `06_StackUnwinding` | A raw-pointer leak during unwinding, fixed with `unique_ptr`/RAII, and the catch-cleanup-rethrow alternative. |
| 07 | `07_SourceLocation` | `std::source_location` for logging and inside a custom exception. |
| 08 | `08_StackTrace` | Capturing/formatting a `std::stacktrace`, iterating frames, and an exception carrying both source location and stack trace. |
| 09 | `09_NewFailures` | Catching `std::bad_alloc`, `new(nothrow)`, and a custom `new_handler`. |
| 10 | `10_ConstructorError` | A `Matrix<T>` template showing constructor error handling. |
| 11 | `11_FunctionTryBlock` | A function-try-block catching exceptions from constructor initializers. |

## Build & run

```powershell
./run.ps1 -Chapter 14           # interactive: pick a sample, build & run
./run.ps1 -Verify -Chapter 14   # compile-check every sample (no run)
```

## Notes

- **Data file:** `01_ReadIntegerFile` and `03_ExceptionsAndPolymorphism` read
  `IntegerFile.txt` (included). Run a sample from inside its folder so the file is
  found; without it, the samples take the file-open-error path by design.
- **Intentional aborts/exit codes:** `01_ReadIntegerFile/11_TerminateHandler`
  deliberately terminates; the `06_StackUnwinding` and `09_NewFailures` samples
  intentionally throw/fail and report the error (often exit code 1). `06/01_BadCode`
  intentionally leaks to make the point.
- **Require C++23:** `08_StackTrace/*` need `<stacktrace>`; `std::println`/`<print>`
  and `std::format` are used throughout.
