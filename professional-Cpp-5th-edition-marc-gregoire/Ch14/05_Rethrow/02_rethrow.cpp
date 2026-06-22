/*
 * Chapter 14 - Why throw; and Not throw e;
 *
 * f() catches the exception as a base-class reference (const exception&) and
 * rethrows with throw;. Because throw; rethrows the original object, main()'s
 * more specific catch (const invalid_argument&) still matches. The book uses
 * this to show that writing throw e; instead would slice the object down to the
 * static type exception - so always rethrow with a bare throw;.
 */

#include <print>
#include <stdexcept>
#include <exception>

using namespace std;

void g() { throw invalid_argument { "Some exception" }; }

void f()
{
	try {
		g();
	} catch (const exception& e) {
		println("caught in f(): {}", e.what());
		throw;  // rethrow
	}
}

int main()
{
	try {
		f();
	} catch (const invalid_argument& e) {
		println("invalid_argument caught in main(): {}", e.what());
	} catch (const exception& e) {
		println("exception caught in main(): {}", e.what());
	}
}
