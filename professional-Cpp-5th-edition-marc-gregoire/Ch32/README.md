# Chapter 32 — Incorporating Design Techniques and Frameworks

> **Topic:** A refresher on core C++ syntax (classes, inheritance, lambdas,
> copy-and-swap, exceptions, file I/O, templates, concepts) followed by
> higher-level idioms (RAII, double dispatch, mixins) and an intro to frameworks
> and the MVC paradigm.

## Samples

| # | Folder | What it demonstrates |
|---|--------|----------------------|
| 01 | `01_Simple` | Writing a class from scratch and deriving from it. |
| 02 | `02_LambdaExpression` | A capturing lambda with `ranges::count_if`. |
| 03 | `03_CopyAndSwap` | The copy-and-swap idiom for strong-exception-safe assignment. |
| 04 | `04_Exceptions` | Throwing/catching `std::runtime_error`. |
| 05 | `05_ClassTemplate` | A `SimpleWrapper` class template. |
| 06 | `06_Concepts` | The same wrapper constrained with a `requires` clause. |
| 07 | `07_FileWrite` | Writing to a file with `ofstream` (incl. append mode). |
| 08 | `08_FileRead` | Three ways to read a file (token, whole-file `getline`, `istreambuf_iterator`). |
| 09 | `09_RAII` | A `File` RAII wrapper around `std::FILE`, plus a `[[nodiscard]]` variant. |
| 10 | `10_DoubleDispatch` | Type-pair dispatch: brute-force `typeid`, single polymorphism, then true double dispatch. |
| 11 | `11_Mixin` | A mixin three ways: template-deriving-from-`T`, CRTP, and C++23 deducing-`this`. |

## Build & run

```powershell
./run.ps1 -Chapter 32           # interactive: pick a sample, build & run
./run.ps1 -Verify -Chapter 32   # compile-check every sample (no run)
```

## Notes

- `08_FileRead` reads `FileWrite.out` — run `07_FileWrite` first (it creates that file),
  from the same working directory.
- `09_RAII` expects an `input.txt`; the RAII wrapper handles its absence gracefully.
- `08_FileRead`, `10_DoubleDispatch`, and `11_Mixin` each contain several files with their
  own `main()` — pick one at a time with `run.ps1`.
