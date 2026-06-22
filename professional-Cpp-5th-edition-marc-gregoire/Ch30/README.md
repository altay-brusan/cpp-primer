# Chapter 30 — Becoming Adept at Testing

> **Topic:** Unit testing in practice — kinds of testing, writing testable code,
> and a worked example testing a generic object pool with the Microsoft Visual
> C++ Testing Framework.

## Samples

| Folder | What it demonstrates |
|--------|----------------------|
| `ObjectPoolTest` | A unit-test project: an `ObjectPool<T>` (with a `Serial` test subject) exercised by a fixture of `TEST_METHOD` tests (creation, acquisition, exclusivity, release/reuse, exception). |

## How to build & run

⚠️ **This chapter does not build with `run.ps1`.** It is a Visual Studio *test
project* (a DLL), not a console program — the files have no `main()` and depend on
the Microsoft Visual C++ Testing Framework (`CppUnitTest.h`,
`Microsoft::VisualStudio::CppUnitTestFramework`).

To run it:

1. Open the solution/folder in Visual Studio.
2. Create (or open) a **Native Unit Test Project**, add `ObjectPool.h`, `Serial.h`,
   `ObjectPoolTest.h`, and `ObjectPoolTest.cpp`.
3. Build, then run the tests from **Test Explorer**.

`ObjectPool.h` and `Serial.h` are reusable header-only templates you can also
`#include` from your own console program if you want to experiment without the test
framework.
