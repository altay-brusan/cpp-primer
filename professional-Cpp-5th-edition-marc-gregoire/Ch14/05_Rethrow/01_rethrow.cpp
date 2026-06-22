/*
 * Chapter 14 - Rethrowing with throw;
 *
 * The bare throw; statement rethrows the exception currently being handled.
 * g() throws an invalid_argument; f() catches it, logs a message, and rethrows
 * with throw; main() then catches the same exception again. Rethrowing lets an
 * intermediate handler react to an error without consuming it.
 */

#include <print>
#include <stdexcept>

using namespace std;

void g()
{
	throw invalid_argument{ "Some exception" };
}

void f()
{
	try {
		g();
	} catch (const invalid_argument& e) {
		println("caught in f(): {}", e.what());
		throw;  // rethrow
	}
}

int main()
{
	try {
		f();
	} catch (const invalid_argument& e) {
		println("caught in main(): {}", e.what());
	}
}