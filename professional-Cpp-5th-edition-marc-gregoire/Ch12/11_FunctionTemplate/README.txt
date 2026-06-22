Two independent programs about function templates:
  01_FindTemplate.cpp        - the generic Find with template-argument deduction.
  02_FindTemplateOverload.cpp - same Find plus a non-template overload for const char*.

01 needs the SpreadsheetCell helper. 02 does not.

Compile each program separately:
  cl /std:c++latest /EHsc 01_FindTemplate.cpp SpreadsheetCell.cpp
  cl /std:c++latest /EHsc 02_FindTemplateOverload.cpp
