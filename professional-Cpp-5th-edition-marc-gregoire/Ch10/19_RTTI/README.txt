Two independent programs about Run-Time Type Information (RTTI):
  01.cpp - typeid for type-tagged dispatch (an anti-pattern, but it works).
  02.cpp - typeid(...).name() for logging - the actual legitimate use case.

Compile each file separately, e.g.:
  cl /std:c++latest /EHsc 01.cpp
