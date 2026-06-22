Two independent programs about virtual base classes:
  01_VirtualBaseClasses.cpp        - diamond resolution via virtual inheritance.
  02_VirtualBaseClasses_Ctors.cpp  - why the most-derived class must init the virtual base.

Compile each file separately, e.g.:
  cl /std:c++latest /EHsc 01_VirtualBaseClasses.cpp
