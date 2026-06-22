/*
 * Chapter 34 - Exporting a C++ Function from a DLL for C# Interop
 *
 * The C++ side of calling C++ from C#. This file is built as a dynamic library
 * (DLL), not a program, so it has no main(). functionInDLL() accepts a Unicode
 * string and returns an int. It is declared extern "C" to suppress C++ name
 * mangling so the C# P/Invoke layer can find it by a simple name, and uses the
 * MSVC-specific __declspec(dllexport) to export it. C# then reaches it via a
 * DllImport attribute from the System.Runtime.InteropServices namespace.
 *
 * Key notes:
 *   - Build as a Windows DLL; __declspec(dllexport) is MSVC-specific.
 */

#include <format>
#include <iostream>

using namespace std;

extern "C"
{
	__declspec(dllexport) int functionInDLL(const wchar_t* p)
	{
		wcout << format(L"The following string was received by C++: '{}'", p) << endl;
		return 42;    // Return some value...
	}
}
