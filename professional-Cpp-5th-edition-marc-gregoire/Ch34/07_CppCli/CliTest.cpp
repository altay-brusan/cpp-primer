/*
 * Chapter 34 - C++/CLI: Consuming a C# Library from C++
 *
 * This is C++/CLI, a Microsoft .NET dialect of C++, not standard ISO C++. It
 * consumes a managed C# class (MyLibrary::MyClass) directly from C++ code. CLI
 * objects live on the garbage-collected heap, so it creates the instance with
 * gcnew and holds it through a handle type (MyClass^, "hat") instead of a raw
 * or smart pointer. main() takes a managed array of System::String handles.
 *
 * Key notes:
 *   - Must be compiled with the /clr switch and linked against the C# assembly.
 */

#include <iostream>

using namespace System;
using namespace MyLibrary;

int main(array<System::String^>^ args)
{
	MyClass^ instance{ gcnew MyClass() };
	auto result{ instance->DoubleIt(1.2) };
	std::cout << result << std::endl;

	result = instance->TripleIt(11.22);
	std::cout << result << std::endl;
}

