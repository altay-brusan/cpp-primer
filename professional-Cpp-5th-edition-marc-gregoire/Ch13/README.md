# Chapter 13 — Demystifying C++ I/O

> **Topic:** C++ streams as a flexible, object-oriented I/O model — console and
> file input/output via `<<`/`>>`, raw stream methods, error handling,
> manipulators, string and span-based streams, random access, and the
> `<filesystem>` library for paths and directories.

## Samples

| # | Folder | What it demonstrates |
|---|--------|----------------------|
| 01 | `01_OutputBasics` | Output with `<<`, chaining, and `endl` vs `\n`. |
| 02 | `02_Write` | Raw character-array output with `cout.write()`. |
| 03 | `03_Put` | Raw single-character output with `cout.put()`. |
| 04 | `04_Flush` | Forcing buffered output out with `flush()`. |
| 05 | `05_Exceptions` | Making streams throw `ios_base::failure` via `exceptions()`. |
| 06 | `06_Manipulator` | Output manipulators (`boolalpha`, `setw`, `setfill`, `put_money`, `quoted`…) and `setprecision` vs `precision()`. |
| 07 | `07_Input` | Reading with `>>`: a string, an int, and mixed reservation data. |
| 08 | `08_ErrorCheck` | The robust input loop using `good()`/`eof()`/`fail()`/`clear()`. |
| 09 | `09_Get` | Raw character input with `get()` to keep whitespace. |
| 10 | `10_Unget` | Pushing a character back with `unget()`. |
| 11 | `11_Putback` | Replacing the next character with `putback(c)`. |
| 12 | `12_Peek` | Looking ahead without consuming via `peek()`. |
| 13 | `13_Getline` | Line input with `getline()`, including a custom delimiter. |
| 14 | `14_Muffin` | Object output the `output()` way vs a custom `std::formatter`. |
| 15 | `15_CustomManipulators` | Writing a custom no-arg manipulator (`tab`). |
| 16 | `16_StringStream` | Building text with `ostringstream`; parsing with `istringstream`. |
| 17 | `17_SpanBasedStream` | C++23 `ispanstream` / `ospanstream` over fixed buffers. |
| 18 | `18_FileStream` | Writing to a file with `ofstream` and open modes. |
| 19 | `19_Seeking` | Random access with `seekp`/`tellp`/`seekg`/`tellg`. |
| 20 | `20_tie` | Flush-on-access linking of streams with `tie()`. |
| 21 | `21_ReadEntireFile` | Slurping a whole file with `getline(…, '\0')`. |
| 22 | `22_Bidirectional` | In-place record editing with `fstream`. |
| 23 | `23_Filesystem` | `<filesystem>` tour: path construction/append/concat, component iteration, decomposition, `directory_entry`, `space()`, and directory iteration. |

## Build & run

From the project root:

```powershell
./run.ps1 -Chapter 13           # interactive: pick a sample, build & run
./run.ps1 -Verify -Chapter 13   # compile-check every sample (no run)
```

## Notes

- **Wait for keyboard input** (run them and type): `07_Input/*`, `08_ErrorCheck`,
  `09_Get`, `10_Unget`, `11_Putback`, `12_Peek`, `13_Getline/*`, `16_StringStream/01`.
- **Need a data file in the sample folder** at run time: `20_tie` (`input.txt`),
  `21_ReadEntireFile` (`some_data.txt`, provided), `22_Bidirectional` (`data.txt`, provided).
- **Platform/environment dependent output:** `23_Filesystem/06`–`09` reference
  Windows-style paths (e.g. `c:/windows/win.ini`, `D:\Foo\Bar`); they compile and
  run everywhere but print machine-specific results (and nothing if a path is absent).
- **Compiler note:** `06_Manipulator/01` wraps `put_money(string{"120000"})` instead
  of the book's `put_money("120000")` — the newest MSVC STL requires a `long double`
  or `std::basic_string` argument (N5032 [ext.manip]/5). Behavior is identical.
- Samples assume a C++23 toolchain (`<print>`, `<spanstream>`, `std::formatter`).
