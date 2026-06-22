Five independent programs about constructor inheritance:
  01.cpp - constructors are NOT inherited by default; manual forwarding.
  02.cpp - `using Base::Base;` pulls them all in.
  03.cpp - Derived ctors hide inherited ones with the same signature.
  04.cpp - Multiple inheritance: both bases provide Base(float), Derived disambiguates.
  05.cpp - Inherited ctors don't touch new Derived members; rely on in-class defaults.

Compile each file separately, e.g.:
  cl /std:c++latest /EHsc 01.cpp
