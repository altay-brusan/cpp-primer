/*
 * Chapter 34 - C++/CLI: A Managed ref class Callable from C#
 *
 * The other direction of C++/CLI interop: a managed "ref class" written in C++
 * that can be consumed by any CLI language, such as C#. Declaring it "public
 * ref class" makes MyCppRefClass a .NET type whose lifetime is handled by the
 * garbage collector, so C# code can instantiate it with new and call TripleIt.
 * This is C++/CLI, not standard ISO C++.
 *
 * Key notes:
 *   - Must be compiled with the /clr switch into a .NET assembly.
 */

#pragma once

using namespace System;

namespace MyCppLibrary
{
	public ref class MyCppRefClass
	{
	public:
		double TripleIt(double value) { return value * 3.0; }
	};
}
