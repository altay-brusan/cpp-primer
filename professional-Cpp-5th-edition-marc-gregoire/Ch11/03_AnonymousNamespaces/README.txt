Two-file program that DELIBERATELY fails at the link step:

Compile both files together, e.g.:
  cl /std:c++latest /EHsc FirstFile.cpp AnotherFile.cpp

Expected outcome:
  - Both files compile cleanly.
  - The linker reports an unresolved external symbol for `f()` because the
    definition in AnotherFile.cpp lives in an anonymous namespace (internal
    linkage).

To make it link, remove the `namespace { ... }` brackets in AnotherFile.cpp.
