/*
 * Chapter 1 - Working with Pointers
 *
 * A pointer is a variable that holds the address of another object. "int*" reads as "pointer
 * to int". The "&" operator takes the address of a variable; "*" dereferences a pointer to
 * reach the pointed-to value. Memory in a C++ program is split between the stack (automatic,
 * scope-bounded) and the free store / heap (manual, lives until you delete it).
 *
 * Key notes:
 *   - Always initialize pointers. Reach for nullptr when you have nothing to point at:
 *         int* p { nullptr };
 *     Dereferencing an uninitialized or null pointer is undefined behavior.
 *   - new/delete pair up: every "new T" needs a matching "delete p;"; every "new T[n]" needs
 *     a matching "delete[] p;". Mismatching them is undefined behavior.
 *   - After delete, set the pointer back to nullptr to prevent use-after-free.
 *   - For class/struct pointers, "p->m" is the shorthand for "(*p).m".
 *   - Short-circuit guards are idiomatic: "if (p && p->salary > 0) { ... }" - if p is null,
 *     the right side is not evaluated.
 *   - In modern C++, raw owning pointers are discouraged. Use std::unique_ptr or
 *     std::shared_ptr (Chapter 7) when one object owns the resource. Use a raw pointer only
 *     as a non-owning observer that may be null.
 *   - Avoid the C functions malloc()/free(); use new/delete or - better - smart pointers.
 *
 * Example:
 *     auto p = std::make_unique<Employee>('J', 'D', 42, 80'000);   // owns the object
 *     p->salary = 90'000;                                          // -> through unique_ptr
 *     // no delete needed - destruction is automatic
 */

#include <print>

using namespace std;

struct Employee {
	char firstInitial;
	char lastInitial;
	int  employeeNumber;
	int  salary{ 75'000 };
};

int main()
{
	{
		int* myIntegerPointer{ nullptr };
		if (!myIntegerPointer) { /* myIntegerPointer is a null pointer */ }
		myIntegerPointer = new int;
		*myIntegerPointer = 8;
		delete myIntegerPointer;
		myIntegerPointer = nullptr;
	}


	{
		int i{ 8 };
		int* myIntegerPointer{ &i };  // Points to the variable with the value 8
	}


	{
		Employee* anEmployee{ new Employee{ 'J', 'D', 42, 80'000 } };
		
		println("{}", (*anEmployee).salary);
		println("{}", anEmployee->salary);
		
		bool isValidSalary1{ anEmployee && anEmployee->salary > 0 };
		bool isValidSalary2{ anEmployee != nullptr && anEmployee->salary > 0 };

		delete anEmployee; anEmployee = nullptr;
	}
}
