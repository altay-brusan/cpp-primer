/*
 * Chapter 19 - Pointers to Member Functions
 *
 * Demonstrates taking the address of a non-static class method and calling it through an
 * object. Unlike a plain function pointer, a pointer to a non-static member must be
 * dereferenced in the context of an instance. The first block uses auto to deduce the
 * member-pointer type (&Employee::getSalary) and invokes it on an object with the .*
 * operator: (employee.*functionPtr)(). The second block uses the fully spelled-out type
 * int (Employee::*)() const and invokes through an object pointer with the ->* operator.
 *
 * Key notes:
 *   - The & before &Employee::getSalary is required for member pointers.
 *   - Parentheses around (employee.*functionPtr) are needed because the call operator
 *     binds tighter than .* and ->* .
 *   - Commented-out lines show the equivalent explicit-type and type-alias declarations.
 */
#include "Employee.h"
#include <print>

using namespace std;
using namespace Records;

int main()
{
	{
		// Old style:
		//int (Employee::*functionPtr) () const { &Employee::getSalary };

		// Using a type alias:
		//using PtrToGet = int (Employee::*) () const;
		//PtrToGet functionPtr{ &Employee::getSalary };

		// Using auto:
		auto functionPtr{ &Employee::getSalary };

		Employee employee{ "John", "Doe" };
		println("{}", (employee.*functionPtr)());
	}

	{
		int (Employee::*functionPtr) () const { &Employee::getSalary };
		Employee johnD{ "John", "Doe" };
		Employee* employee{ &johnD };
		println("{}", (employee->*functionPtr)());
	}
}
