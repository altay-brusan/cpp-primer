# Chapter 21 — String Localization and Regular Expressions

> **Topic:** Making programs locale-aware (wide/Unicode character types,
> `std::locale`, facets) and pattern matching with the `<regex>` library.

## Samples

| # | Folder | What it demonstrates |
|---|--------|----------------------|
| 01 | `01_WideStrings` | `wchar_t`, `L"…"` literals, `wcout`, and the wide overload of `std::format`. |
| 02 | `02_CharTypes` | `char8_t`/`char16_t`/`char32_t`/`wchar_t`, the `u8`/`u`/`U`/`L`/`R` prefixes, and `\u`/`\N{}` escapes. |
| 03 | `03_Localization` | Why sentences must not be built by concatenating literals (word order varies by language). |
| 04 | `04_Locales` | `locale::global()`, stream `imbue()`, `{:L}` locale-aware formatting, querying `locale::name()`, and locale-parameterized `isupper`/`toupper`. |
| 05 | `05_Facets` | `use_facet<moneypunct>` for currency symbols and the `codecvt` facet for encoding conversion. |
| 06 | `06_RegularExpressions` | `regex_match`/`regex_search`, `smatch` capture groups, `sregex_iterator`, `sregex_token_iterator` (incl. field splitting), and `regex_replace`. |

## Build & run

```powershell
./run.ps1 -Chapter 21           # interactive: pick a sample, build & run
./run.ps1 -Verify -Chapter 21   # compile-check every sample (no run)
```

## Notes

- **Wait for keyboard input** (loop until you type `q`): all of
  `06_RegularExpressions/01–07` and `10`.
- **Locale availability:** the `04_Locales`/`05_Facets` samples construct locales like
  `en-US`, `en-GB`, `fr-FR`; constructing a locale throws at runtime if it isn't
  installed on the system.
- `05_Facets/02_codecvt` uses `<codecvt>`, deprecated since C++17 (compiles with a
  warning under `/W4`).
- `02_CharTypes` and the `<print>`/`std::format` usage assume a C++23 toolchain and
  UTF-8 console support.
