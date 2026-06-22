Two-file program. As-shipped, it links and runs.

Compile both files together, e.g.:
  cl /std:c++latest /EHsc FirstFile.cpp AnotherFile.cpp

The point of the example is to compare with sample 03 (anonymous namespaces):
both `static` and `namespace { ... }` give a function internal linkage.

To watch the link break, uncomment the `static void f();` line in
AnotherFile.cpp.
