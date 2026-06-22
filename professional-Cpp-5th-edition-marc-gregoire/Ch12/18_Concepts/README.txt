Six independent programs about concepts (C++20):
  01_Big.cpp                       - defining a concept with sizeof.
  02_Incrementable.cpp             - requires-expressions + all the ways to apply them.
  03_Subsumption.cpp               - overload resolution between constraints.
  04_GameBoard.cpp                 - constraining a class template (derived_from).
  05_GameBoardMemberFunction.cpp   - constraining a single member function (movable).
  06_ConstraintBasedSpecialization.cpp - subsumption used as "partial specialization" for functions.

Compile each program separately (each has its own main):
  cl /std:c++latest /EHsc 01_Big.cpp
  ...
