/*
 * Chapter 9 - Implementing Move Semantics (driver)
 *
 * Drives the Spreadsheet through situations that should trigger moves rather than
 * copies:
 *   - `vec.push_back(Spreadsheet{ ... })` constructs a temporary and pushes it,
 *     invoking the move constructor.
 *   - The second push grows the vector, which moves every existing element into
 *     the new buffer (only possible noexcept-cheaply because the move ctor is
 *     marked noexcept).
 *   - `s = createObject()` assigns from a temporary, hitting the move assignment.
 *   - `s2 = s` copies because `s` is an lvalue, so the copy assignment runs.
 * Watch the printed lines to confirm which member function ran.
 */
#include "Spreadsheet.h"
#include <print>
#include <vector>

using namespace std;

Spreadsheet createObject()
{
	return Spreadsheet { 3, 2 };
}

int main()
{
	vector<Spreadsheet> vec;
	for (size_t i{ 0 }; i < 2; ++i) {
		println("Iteration {}", i);
		vec.push_back(Spreadsheet { 100, 100 });
		println("");
	}

	Spreadsheet s { 2, 3 };
	s = createObject();

	println("");

	Spreadsheet s2 { 5, 6 };
	s2 = s;
}
