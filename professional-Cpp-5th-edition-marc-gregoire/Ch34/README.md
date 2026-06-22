# Chapter 34 — Developing Cross-Platform and Cross-Language Applications

> **Topic:** Writing C++ that ports across platforms (data/pointer sizes,
> endianness, compiler extensions) and that interoperates with other languages
> (C, C#, Java, Perl).

## Samples

| # | Folder | What it demonstrates | Builds with plain MSVC? |
|---|--------|----------------------|--------------------------|
| 01 | `01_PtrSize` | `sizeof` a pointer varies by architecture (4 vs 8 bytes). | ✅ |
| 02 | `02_Endian` | Big- vs little-endian via C++20 `std::endian`. | ✅ |
| 03 | `03_VariableArray` | A variable-length array — a **g++ extension**, not standard C++. | ❌ rejected by MSVC (by design) |
| 04 | `04_MixingC` | Uses `class` as a variable name — legal **C**, illegal C++. | ❌ needs a C compiler (by design) |
| 05 | `05_networklib` | Wrapping a procedural C networking library in RAII/facade C++ classes. | ✅ |
| 06 | `06_CSharp` | A C++ DLL function exported `extern "C"` for C# P/Invoke. | builds as a **DLL** (no `main`) |
| 07 | `07_CppCli` | C++/CLI consuming a C# class and a managed `ref class`. | ❌ needs `/clr` + the C# assembly |
| 08 | `08_JNI` | A C++ implementation of a Java `native` method via JNI. | needs a **JDK** (`jni.h`), builds as a shared lib |
| 09 | `09_Perl` | A C++ program driven by a Perl script through `argv`/exit code. | ✅ |

The `.cs`, `.java`, and `.pl` files are the *other-language* sides of the interop
examples — build/run them with their own toolchains (C#, JDK, Perl).

## Build & run

```powershell
./run.ps1 -Chapter 34           # interactive: pick a sample, build & run
./run.ps1 -Verify -Chapter 34   # compile-check the plain-C++ samples
```

`run.ps1 -Verify` will report `03_VariableArray`, `04_MixingC`, and `07_CppCli` as
**FAIL** — that is expected: they are deliberately non-portable or require a different
compiler/toolchain, which is the whole point of this chapter. `06_CSharp` and `08_JNI`
have no `main()` (they're libraries) and are skipped by the runner.

## Notes

- `05_networklib` compiles as one MSVC project — `Test.cpp` links the rest of the folder.
- To actually exercise the interop samples you need the matching toolchains: the .NET SDK
  (C#/CLI), a JDK (`javac`/`javah` + JNI), and Perl.
