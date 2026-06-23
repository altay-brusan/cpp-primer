# C++ Software Design (Klaus Iglberger) — Annotated Guideline Samples

Working through Klaus Iglberger's **C++ Software Design: Design Principles and
Patterns for High-Quality Software** (O'Reilly), one **Guideline** at a time. Each
of the book's **39 guidelines** gets its own folder containing self-contained,
runnable C++ that demonstrates the guideline, with the **design concern explained
as comprehensive comments**, plus a `README.md` summarizing the concern.

Most pattern guidelines show a **problem → solution** progression as numbered
sub-folders, so you can build and run the "before" and "after" side by side. The
code is **standard-library-only** and targets **C++23** (built/verified with MSVC,
Visual Studio "Desktop development with C++" workload). Where the book uses a
third-party library, it's replaced with a tiny inline stub so everything compiles
out of the box — the *design* point is preserved, not the exact includes.

> These are study notes and original illustrative code, not the book's text. The
> author's official companion code lives at
> <https://github.com/igl42/cpp_software_design>.

---

## Quick start

From this folder, in PowerShell:

```powershell
./run.ps1                          # interactive: pick a guideline, then a sample; builds & runs
./run.ps1 -List                    # list all 39 guidelines
./run.ps1 -Guideline 19            # jump to guideline 19's sample menu
./run.ps1 -Guideline 19 -Sample 2  # build & run sample 2 of guideline 19
./run.ps1 -NoRun -Guideline 32 -Sample 1   # build only, don't run
./run.ps1 -Verify -Guideline 32    # compile-check every sample in a guideline (no run)
./run.ps1 -Verify                  # compile-check every sample in every guideline
```

`run.ps1` finds Visual Studio automatically (via `vswhere` + `vcvars64`), compiles
the selected sample's `main()` file together with any sibling helper `.cpp` files,
and writes build output to a gitignored `.build/` folder so the source tree stays
clean. Conceptual guidelines (e.g. 1, 10–12, 14, 39) are **README-only** and have
no samples to run.

### Requirements
- Windows with **Visual Studio 2022/2026** and the **Desktop development with C++**
  workload (provides `cl.exe`, the C++23 standard library, and `vcvars64`).
- PowerShell (ships with Windows).

### Compiling a single file yourself
Every sample is plain standard C++ — you can also compile one directly:

```powershell
cl /nologo /std:c++latest /EHsc /utf-8 Guideline19_Strategy\02_Solution_Strategy\main.cpp
```

---

## Guidelines

### Part — The Art of Software Design
| # | Guideline | Topic |
|---|-----------|-------|
| [1](Guideline01_ImportanceOfDesign) | Understand the Importance of Software Design | design vs features; managing dependencies *(README)* |
| [2](Guideline02_DesignForChange) | Design for Change | SRP / DRY; separate concerns |
| [3](Guideline03_SeparateInterfaces) | Separate Interfaces to Avoid Artificial Coupling | Interface Segregation |
| [4](Guideline04_DesignForTestability) | Design for Testability | extract private logic as free functions |
| [5](Guideline05_DesignForExtension) | Design for Extension | Open-Closed Principle |

### The Art of Building Abstractions
| # | Guideline | Topic |
|---|-----------|-------|
| [6](Guideline06_ExpectedBehavior) | Adhere to the Expected Behavior of Abstractions | Liskov Substitution |
| [7](Guideline07_BaseClassesVsConcepts) | Base Classes vs Concepts | runtime vs compile-time abstraction |
| [8](Guideline08_OverloadSets) | Semantic Requirements of Overload Sets | overload sets as customization points |
| [9](Guideline09_OwnershipOfAbstractions) | Ownership of Abstractions | Dependency Inversion + who owns the interface |
| [10](Guideline10_ArchitecturalDocument) | Consider Creating an Architectural Document | architecture as shared understanding *(README)* |

### The Purpose of Design Patterns
| # | Guideline | Topic |
|---|-----------|-------|
| [11](Guideline11_PurposeOfPatterns) | Understand the Purpose of Design Patterns | name + intent + abstraction *(README)* |
| [12](Guideline12_PatternMisconceptions) | Beware of Design Pattern Misconceptions | a tool, not a goal *(README)* |
| [13](Guideline13_PatternsAreEverywhere) | Design Patterns Are Everywhere | patterns in the Standard Library |
| [14](Guideline14_NameToCommunicateIntent) | Use a Pattern's Name to Communicate Intent | names as shared vocabulary *(README)* |
| [15](Guideline15_AdditionOfTypesOrOperations) | Design for the Addition of Types or Operations | the expression problem |

### The Visitor Design Pattern
| # | Guideline | Topic |
|---|-----------|-------|
| [16](Guideline16_Visitor) | Use Visitor to Extend Operations | classic GoF Visitor |
| [17](Guideline17_StdVariantVisitor) | Consider std::variant for Implementing Visitor | value-based visitor |
| [18](Guideline18_AcyclicVisitorPerformance) | Beware the Performance of Acyclic Visitor | dynamic_cast dispatch cost |

### The Strategy and Command Design Patterns
| # | Guideline | Topic |
|---|-----------|-------|
| [19](Guideline19_Strategy) | Use Strategy to Isolate How Things Are Done | Strategy |
| [20](Guideline20_CompositionOverInheritance) | Favor Composition over Inheritance | M+N vs M*N |
| [21](Guideline21_Command) | Use Command to Isolate What Things Are Done | Command + undo |
| [22](Guideline22_ValueSemantics) | Prefer Value Semantics over Reference Semantics | value vs reference semantics |
| [23](Guideline23_ValueBasedStrategyCommand) | Value-Based Strategy and Command | std::function implementations |

### The Adapter, Observer, and CRTP Design Patterns
| # | Guideline | Topic |
|---|-----------|-------|
| [24](Guideline24_Adapter) | Use Adapters to Standardize Interfaces | Adapter (object/class/std) |
| [25](Guideline25_Observer) | Apply Observers as a Notification Mechanism | Observer (push/pull) |
| [26](Guideline26_CRTPStaticTypeCategories) | Use CRTP for Static Type Categories | CRTP vs concepts |
| [27](Guideline27_CRTPMixin) | Use CRTP for Static Mixin Classes | CRTP mixins / strong types |

### The Bridge, Prototype, and External Polymorphism Patterns
| # | Guideline | Topic |
|---|-----------|-------|
| [28](Guideline28_Bridge) | Build Bridges to Remove Physical Dependencies | Bridge / Pimpl |
| [29](Guideline29_BridgePerformance) | Bridge Performance Gains and Losses | partial Bridge; measure |
| [30](Guideline30_Prototype) | Apply Prototype for Abstract Copy | virtual clone() |
| [31](Guideline31_ExternalPolymorphism) | Use External Polymorphism | nonintrusive runtime polymorphism |

### The Type Erasure Design Pattern
| # | Guideline | Topic |
|---|-----------|-------|
| [32](Guideline32_TypeErasure) | Replace Inheritance Hierarchies with Type Erasure | the owning value wrapper |
| [33](Guideline33_TypeErasureOptimization) | Optimization Potential of Type Erasure | SBO + manual dispatch |
| [34](Guideline34_TypeErasureSetupCosts) | Setup Costs of Owning Type Erasure Wrappers | non-owning views |

### The Decorator Design Pattern
| # | Guideline | Topic |
|---|-----------|-------|
| [35](Guideline35_Decorator) | Use Decorators to Add Customization Hierarchically | Decorator |
| [36](Guideline36_RuntimeVsCompileTimeAbstraction) | Runtime vs Compile-Time Abstraction | the trade-off |

### The Singleton Pattern
| # | Guideline | Topic |
|---|-----------|-------|
| [37](Guideline37_SingletonImplementationPattern) | Singleton as an Implementation Pattern | Meyers' singleton |
| [38](Guideline38_SingletonForChangeAndTestability) | Design Singletons for Change and Testability | invert the dependency |

### The Last Guideline
| # | Guideline | Topic |
|---|-----------|-------|
| [39](Guideline39_ContinueToLearn) | Continue to Learn About Design Patterns | keep studying *(README)* |

---

## Notes

- **Every code sample compiles** on the installed MSVC (`run.ps1 -Verify`). Samples
  are standard-library-only and self-contained per folder.
- A few samples are **micro-benchmarks** (e.g. 29, 33, 34) — build them in release
  for meaningful timings; the debug build `run.ps1` produces is slower.
- "Problem" samples demonstrate a *design* flaw but still compile and run; any code
  that genuinely wouldn't compile is shown commented-out with an explanation.
- Build artifacts are never committed (`.gitignore` excludes `*.exe`/`*.obj`/… and
  the `.build/` output directory).
