Two-file program demonstrating an extern global variable.

Compile both files together, e.g.:
  cl /std:c++latest /EHsc FirstFile.cpp AnotherFile.cpp

Expected output:
  3

Layout:
  - FirstFile.cpp    - `extern int x;` declaration + main() that prints x.
  - AnotherFile.cpp  - actual definition `int x{3};`.
