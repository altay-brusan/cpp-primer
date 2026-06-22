/*
 * Chapter 1 - Designated Initializers
 *
 * C++20 designated initializers let you initialize aggregate members by name. Each entry
 * starts with a dot, names the member, and assigns a value. Far more readable than relying
 * on positional order for a struct with many fields.
 *
 * Key notes:
 *   - Restricted to aggregates: only public data members, no user-declared constructors,
 *     no virtual functions, no virtual/private/protected base classes.
 *   - Names must appear in declaration order. You can omit members - they fall back to their
 *     in-class initializer (here "salary { 75'000 }") or zero initialization.
 *   - Mixing designated and positional initializers in the same braces is not allowed.
 *   - Adding a new data member to the struct does not break existing call sites that use
 *     designated initializers - the new member just takes its default.
 *   - In C this feature has slightly looser rules (any order, mixing allowed); C++ is
 *     stricter.
 *
 * Example:
 *     Employee e {
 *         .firstInitial = 'J',
 *         .lastInitial  = 'D',
 *         .salary       = 80'000   // employeeNumber omitted -> zero-initialized
 *     };
 */

struct Employee {
	char firstInitial;
	char lastInitial;
	int  employeeNumber;
	int  salary{ 75'000 };
};

int main()
{
	// Initialize all data members
	Employee anEmployee1{
		.firstInitial = 'J',
		.lastInitial = 'D',
		.employeeNumber = 42,
		.salary = 80'000
	};

	// Initialize all data members, except employeeNumber
	Employee anEmployee2{
		.firstInitial = 'J',
		.lastInitial = 'D',
		.salary = 80'000
	};

	// Initialize all data members, except employeeNumber, and salary
	Employee anEmployee3{
		.firstInitial = 'J',
		.lastInitial = 'D'
	};
}
