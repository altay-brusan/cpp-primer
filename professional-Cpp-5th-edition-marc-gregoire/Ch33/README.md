# Chapter 33 — Applying Design Patterns

> **Topic:** Worked C++ implementations of the classic (Gang-of-Four-style)
> design patterns.

## Samples

| # | Folder | Pattern |
|---|--------|---------|
| 01 | `01_Strategy` | **Dependency Injection** — `Foo` receives an `ILogger*` through its constructor (folder is named "Strategy"; the code/book section is Dependency Injection). |
| 02 | `02_AbstractCarFactory` | **Abstract Factory** — `ICarFactory` builds a family of products (`makeSedan`/`makeSuv`). |
| 03 | `03_CarFactory` | **Factory Method** — `requestCar()` delegates to an overridable `createCar()`. |
| 04 | `04_PimplAlternative` | **Factory Method** as a pimpl alternative — a static `create()` hides `FooImpl`. |
| 05 | `05_LoggerAdapter` | **Adapter** — `AdaptedLogger` wraps an existing `Logger` behind a simpler interface. |
| 06 | `06_Proxy` | **Proxy** — `PlayerProxy` stands in for `Player`, adding a connectivity check. |
| 07 | `07_Observer` | **Observer** — a variadic `Event<...>` registers and notifies callbacks. |
| 08 | `08_Decorator` | **Decorator** — `BoldParagraph`/`ItalicParagraph` augment `getHTML()`, nestable. |
| 09 | `09_ChainOfResponsibility` | **Chain of Responsibility** — handlers each handle one event and forward the rest. |
| 10 | `10_SingletonLogger` | **Singleton** — `Logger` with a thread-safe `instance()` accessor. |

## Build & run

```powershell
./run.ps1 -Chapter 33           # interactive: pick a sample, build & run
./run.ps1 -Verify -Chapter 33   # compile-check every sample (no run)
```

## Notes

- Most patterns are a set of headers (+ a helper `.cpp`) plus a driver `*Test.cpp` /
  pattern `.cpp`; `run.ps1` compiles the driver with its sibling `.cpp`.
- The logger drivers (`01_Strategy`, `10_SingletonLogger`) write a `log.out` file.
