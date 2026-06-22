# Chapter 24 — Additional Library Utilities

> **Topic:** Vocabulary types and helpers — `std::variant` and `std::any`,
> `std::pair`/`std::tuple` and their utilities, plus `std::optional` and
> `std::expected`.

## Samples

| # | Folder | What it demonstrates |
|---|--------|----------------------|
| 01 | `01_variant` | `std::variant` tagged union: `monostate`, `index()`/`holds_alternative`, `get`/`get_if`, `visit`. |
| 02 | `02_any` | `std::any` holding any type: `has_value()`, `type()`, `any_cast`/`bad_any_cast`, `vector<any>`. |
| 03 | `03_tuple` | `pair`, `tuple` (`get`, `tuple_element`/`tuple_size`), structured bindings, `tie`/`ignore`, `tuple_cat`, comparisons, `operator<=>` via `tie`, `make_from_tuple`, `apply`. |
| 04 | `04_optional` | `std::optional` with C++23 monadic `and_then`/`transform`/`or_else`. |
| 05 | `05_expected` | `std::expected<T,E>` with `unexpected`, value/error access, and `and_then`. |

## Build & run

```powershell
./run.ps1 -Chapter 24           # interactive: pick a sample, build & run
./run.ps1 -Verify -Chapter 24   # compile-check every sample (no run)
```

## Notes

- **Wait for keyboard input:** `04_optional` (reads integers from `cin` until EOF/`q`).
- **No visible output:** `03_tuple/08_make_from_tuple` (only constructs an object).
- Uses C++23 features (`std::print`/`println`, `std::expected`, monadic `optional`).
