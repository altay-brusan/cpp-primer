Four independent programs about the C++ casts:
  01_static_cast.cpp      - static_cast for everyday conversions.
  02_reinterpret_cast.cpp - reinterpret_cast for unrelated pointer/reference types.
  03_bit_cast.cpp         - std::bit_cast (C++20) - safe bit-pattern conversion.
  04_dynamic_cast.cpp     - dynamic_cast - checked downcast in polymorphic hierarchies.

Compile each file separately, e.g.:
  cl /std:c++latest /EHsc 01_static_cast.cpp
