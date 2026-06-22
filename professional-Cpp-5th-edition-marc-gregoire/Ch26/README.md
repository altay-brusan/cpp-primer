# Chapter 26 — Advanced Templates

> **Topic:** The deeper template machinery — the three kinds of template
> parameters, full and partial specialization, variadic templates and fold
> expressions, template metaprogramming, type traits, SFINAE/`enable_if`, and
> concepts.

## Samples

| # | Folder | What it demonstrates |
|---|--------|----------------------|
| 01–03 | `01_GridTemplateContainer…` | A second template parameter choosing the underlying container — concept-constrained, with a default, and as a template-template parameter. |
| 04 | `04_GridDefaultElementValue` | A non-type template parameter supplying the default cell value. |
| 05–06 | `05_GridPartialString`, `06_GridPartialPtr` | Class-template partial specialization for `const char*` and for pointer types. |
| 07 | `07_FunctionTemplatePtr` | Overloading a function template to emulate partial specialization. |
| 08–09 | `08_OneDGrid`, `09_NDGrid` | Building an N-dimensional grid via template recursion. |
| 10 | `10_VarArgs` | Type-safe variadic templates: recursion, perfect forwarding, `constexpr if` termination. |
| 11 | `11_VariadicMixins` | A parameter pack as a variable number of mixin base classes. |
| 12 | `12_Folding` | Fold expressions (comma, binary/unary left, concept-constrained, logical). |
| 13 | `13_Factorial` | Compile-time factorial via recursion and via `consteval`. |
| 14 | `14_LoopUnrolling` | Compile-time loop unrolling through template recursion. |
| 15 | `15_PrintTuple` | Six progressive tuple-printers (recursion → `constexpr if` → `index_sequence` + fold). |
| 16 | `16_TypeTraits` | Fourteen type-trait use cases (categories, tag dispatch, `is_same`, `conditional`, `enable_if`/SFINAE, concepts, `constexpr if`). |
| 17 | `17_StaticAssert` | `static_assert` at namespace scope and combined with a type trait. |

## Build & run

```powershell
./run.ps1 -Chapter 26           # interactive: pick a sample, build & run
./run.ps1 -Verify -Chapter 26   # compile-check every sample (no run)
```

## Notes

- Most samples are a template header plus a `*Test.cpp` driver (`run.ps1` compiles the
  driver with its sibling `.cpp`).
- Several files contain deliberately commented-out "WILL NOT COMPILE" lines
  (e.g. `Grid<int, double>`) — they are inert as shipped.
- `17_StaticAssert` asserts a 64-bit build (`sizeof(void*) == 8`); build for x64.
