# Professional C++ (5th Edition) — Annotated Code Samples

Working through Marc Gregoire's **Professional C++, 5th Edition**, chapter by
chapter. Every sample carries a documentation header summarizing — in the book's
framing — what it demonstrates and the concept behind it, so each file reads as a
self-contained mini-lesson. Each chapter also has a `README.md` with the chapter
**topic**, a per-sample table, and run notes.

The samples target **C++23** and are built/verified with **MSVC** (Visual Studio
2022/2026, "Desktop development with C++" workload).

---

## Quick start

From this folder, in PowerShell:

```powershell
./run.ps1                       # interactive: pick a chapter, then a sample; builds & runs
./run.ps1 -List                 # list all chapters
./run.ps1 -Chapter 13           # jump to chapter 13's sample menu
./run.ps1 -Chapter 13 -Sample 2 # build & run sample 2 of chapter 13
./run.ps1 -Chapter 6 -Sample 1 -File 1   # a sample folder with several runnable files
./run.ps1 -NoRun -Chapter 13 -Sample 2   # build only, don't run
./run.ps1 -Verify -Chapter 13   # compile-check every sample in a chapter (no run)
./run.ps1 -Verify               # compile-check every sample in every chapter
```

`run.ps1` finds Visual Studio automatically (via `vswhere` + `vcvars64`), compiles the
selected sample's `main()` file together with any sibling helper `.cpp` files, and puts
build output in a gitignored `.build/` folder so the source tree stays clean. It runs the
program from its own folder so relative data files resolve.

> First run is slower because it initializes the MSVC environment.

### Compiling a single file yourself

Each sample is just standard C++ — you can also compile one directly:

```powershell
cl /nologo /std:c++latest /EHsc /utf-8 Ch13\01_OutputBasics\OutputBasics.cpp
```

### VS Code

Open the folder in VS Code and use the bundled tasks (Terminal → Run Task):
**“MSVC: Build active file”** and **“MSVC: Build and run active file”** compile the file
currently open in the editor.

---

## Requirements

- Windows with **Visual Studio 2022/2026** and the **Desktop development with C++**
  workload (provides `cl.exe`, the C++23 standard library, and `vcvars64`).
- PowerShell (ships with Windows).
- A few late-chapter samples need extra toolchains — see those chapters' READMEs
  (e.g. Ch30 uses the VS test framework; Ch34 mixes in C#, Java/JNI, and Perl).

---

## Chapters

| Ch | Topic | Notes |
|----|-------|-------|
| [00](Ch00) | Getting started — the `AirlineTicket` warm-up sample | |
| [01](Ch01) | A Crash Course in C++ and the Standard Library | |
| [02](Ch02) | Working with Strings and String Views | |
| [03](Ch03) | Coding with Style | |
| [04](Ch04) | Designing Professional C++ Programs | |
| [05](Ch05) | Designing with Objects | |
| [06](Ch06) | Designing for Reuse | |
| [07](Ch07) | Memory Management | |
| [08](Ch08) | Gaining Proficiency with Classes and Objects | |
| [09](Ch09) | Mastering Classes and Objects | |
| [10](Ch10) | Discovering Inheritance Techniques | |
| [11](Ch11) | Odds and Ends (modules, namespaces, attributes…) | |
| [12](Ch12) | Writing Generic Code with Templates | |
| [13](Ch13) | Demystifying C++ I/O | streams, manipulators, filesystem |
| [14](Ch14) | Handling Errors | exceptions, stacktrace, source_location |
| [15](Ch15) | Overloading C++ Operators | |
| [16](Ch16) | Overview of the C++ Standard Library | |
| [17](Ch17) | Understanding Iterators and the Ranges Library | |
| [18](Ch18) | Standard Library Containers | |
| [19](Ch19) | Function Pointers, Function Objects, and Lambda Expressions | |
| [20](Ch20) | Mastering Standard Library Algorithms | |
| [21](Ch21) | String Localization and Regular Expressions | |
| [22](Ch22) | Date and Time Utilities | `<chrono>`, calendar, time zones |
| [23](Ch23) | Random Number Facilities | `<random>` |
| [24](Ch24) | Additional Library Utilities | variant, any, tuple, optional, expected |
| [25](Ch25) | Customizing and Extending the Standard Library | |
| [26](Ch26) | Advanced Templates | |
| [27](Ch27) | Multithreaded Programming with C++ | |
| [28](Ch28) | Maximizing Software Engineering Methods | conceptual — no code |
| [29](Ch29) | Writing Efficient C++ | |
| [30](Ch30) | Becoming Adept at Testing | VS test project |
| [31](Ch31) | Conquering Debugging | |
| [32](Ch32) | Incorporating Design Techniques and Frameworks | |
| [33](Ch33) | Applying Design Patterns | |
| [34](Ch34) | Developing Cross-Platform and Cross-Language Applications | mixes C#, Java/JNI, Perl |

---

## A few things to know

- **Compiles on the newest MSVC.** Every sample with a `main()` is verified to build with
  the installed MSVC (`run.ps1 -Verify`). A handful of samples needed tiny, standard-correct
  tweaks where the newest MSVC standard library is stricter than the book assumed (e.g.
  `put_money` requires a `std::string`/`long double`; a few `<thread>` samples now need an
  explicit `#include <chrono>`); each such change is noted in the chapter's README.
- **Some samples don't print anything** — they exist to show that an operation compiles, or
  they write an output file (`res.csv`, `log.txt`). Some **wait for keyboard input**, and
  some **need a data file** in the working directory. Each chapter README flags these.
- **Build artifacts are not committed.** `.gitignore` excludes `*.exe`/`*.obj`/`*.pdb`/…
  and the `.build/` output directory.
