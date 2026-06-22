# Chapter 19 — Function Pointers, Function Objects, and Lambda Expressions

> **Topic:** The many forms of C++ callables — function pointers, pointers to
> members, `std::function`/`move_only_function`, function objects and the
> Standard Library function objects, the `bind`/`bind_front` family, lambda
> expressions, and `std::invoke`.

## Samples

| # | Folder | What it demonstrates |
|---|--------|----------------------|
| 01 | `01_FunctionPointers` | C-style function pointers as callbacks, as template params, the C++20 abbreviated form, and resolving a function pointer from a Windows DLL. |
| 02 | `02_PtrsToMemberFunctionsAndMembers` | Pointers to non-static members and the `.*` / `->*` call syntax. |
| 03 | `03_FunctionObjects` | Writing functors; the arithmetic/comparison/logical Standard Library function objects; transparent comparators; `bind`, `ref`, `bind_front`/`bind_back`, `not_fn`, `mem_fn`. |
| 04 | `04_PolymorphicFunctionWrappers` | `std::function` basics & as callback params, and C++23 `move_only_function`. |
| 05 | `05_Lambdas` | Lambda syntax & captures, generic and templated lambdas, capture-init/by-move, returning lambdas, and a C++23 deduced-`this` recursive lambda. |
| 06 | `06_Invokers` | `std::invoke` over functions/lambdas/members and C++23 `invoke_r`. |

## Build & run

```powershell
./run.ps1 -Chapter 19           # interactive: pick a sample, build & run
./run.ps1 -Verify -Chapter 19   # compile-check every sample (no run)
```

## Notes

- **Windows-only:** `01_FunctionPointers/04_MessageBoxA` uses `Windows.h` /
  `LoadLibraryA` / `GetProcAddress` and pops up a GUI message box.
- **Wait for keyboard input:** `03_FunctionObjects/02_Arithmetic` (scores until 0),
  `03_FunctionObjects/06_LogicalFunctors` (flags until -1).
- **No visible console output** (conceptual / effects only): `03_FunctionObjects/05`,
  `/08`, `/09`, `05_Lambdas/05_TemplatedLambda`, `06_Invokers/02_invoke_r`.
- Several samples use C++20/23 features (abbreviated/templated lambdas,
  `move_only_function`, deduced-`this` recursion, `invoke_r`).
