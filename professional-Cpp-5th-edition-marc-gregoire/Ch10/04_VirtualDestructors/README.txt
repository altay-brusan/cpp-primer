Two standalone programs, each with its own main():
  - 01_VirtualDestructors.cpp - deliberately broken: ~Derived never runs.
  - 02_VirtualDestructors.cpp - the fix: virtual ~Base() makes delete chain down.

Compile each file separately, e.g.:
  cl /std:c++latest /EHsc 01_VirtualDestructors.cpp
  cl /std:c++latest /EHsc 02_VirtualDestructors.cpp
