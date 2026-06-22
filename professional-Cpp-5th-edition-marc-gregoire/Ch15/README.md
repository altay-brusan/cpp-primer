# Chapter 15 — Overloading C++ Operators

> **Topic:** The full range of overloadable operators beyond the basics —
> arithmetic and increment/decrement, stream insertion/extraction, subscripting
> (single, multidimensional, static), the function-call operator (functors),
> dereferencing for smart pointers, conversion operators, overloading
> `new`/`delete`, and user-defined literals.

## Samples

| # | Folder | What it demonstrates |
|---|--------|----------------------|
| 01 | `01_ArithmeticOperators` | Non-member binary `+ - * /` forwarding to member `+= -= *= /=`, unary `operator-`, prefix/postfix `++`/`--`, and a defaulted `operator<=>`. |
| 02 | `02_StreamOperators` | Global `operator<<` / `operator>>` (left operand is the stream, so non-members). |
| 03 | `03_SubscriptingOperator` | A growable `Array<T>` with const and non-const `operator[]`. |
| 04 | `04_MultidimensionalSubscriptingOperator` | C++23 two-argument `operator[](x, y)`. |
| 05 | `05_StaticSubscriptingOperator` | C++23 `static operator[]`. |
| 06 | `06_Functors` | A stateful function object (`operator()`) and a C++23 `static operator()`. |
| 07 | `07_DereferenceOps` | A smart-pointer `Pointer<T>` overloading `operator*` and `operator->`. |
| 08 | `08_ConversionsSpreadsheetCell` | Conversion operators `operator double()` and `operator string()`. |
| 09 | `09_OperatorAutoSpreadsheetCell` | The same conversions via `operator auto()`. |
| 10 | `10_ExplicitConversionsSpreadsheetCell` | `explicit operator double()` to resolve ambiguity. |
| 11 | `11_ConversionsPointer` | `operator void*()` for Boolean-context use. |
| 12 | `12_ConversionsPointerBool` | `operator bool()` and its pitfalls (anti-pattern demo). |
| 13 | `13_Memory` | Overloading every form of `operator new`/`operator delete`. |
| 14 | `14_ExplicitDelete` | `= delete`'ing `operator new` to forbid free-store allocation. |
| 15 | `15_UserDefinedLiterals` | Cooked-mode literals `_km`, `_m`, `_s`. |

## Build & run

```powershell
./run.ps1 -Chapter 15           # interactive: pick a sample, build & run
./run.ps1 -Verify -Chapter 15   # compile-check every sample (no run)
```

## Notes

- Most samples split into a class (`*.h` + `*.cpp`) plus a `*Test.cpp` driver;
  `run.ps1` compiles the driver together with its helper `.cpp`.
- **Wait for keyboard input:** `02_StreamOperators/SpreadsheetCellTest`.
- **Intentional "won't compile" lines (commented out on purpose):**
  `14_ExplicitDelete` (allocating a type whose `operator new` is deleted) and
  `12_ConversionsPointerBool` (a `p != nullptr` check that `operator bool()` breaks).
- Several samples use C++23 features (`static operator[]`/`()`, two-arg subscript).
