Four independent programs about changing access in a derived class:
  01.cpp - tightening: public Base::talk overridden as protected.
  02.cpp - protected base function called from a derived public function.
  03.cpp - widening by override: protected -> public AND new body.
  04.cpp - widening by `using`: protected -> public, body unchanged.

Compile each file separately, e.g.:
  cl /std:c++latest /EHsc 01.cpp
