#pragma once

/*
 * Chapter 1 - Structs
 *
 * A struct bundles several existing types into a new aggregate type. The classic example is
 * a database record - here, the data describing one Employee. Members are accessed with the
 * "." operator on an instance, or with "->" through a pointer.
 *
 * Key notes:
 *   - struct and class differ only in default access: struct members are public by default,
 *     class members are private. Pick struct for plain data, class for behavior.
 *   - Aggregate initialization: Employee e { 'J', 'D', 42, 80'000 }; (order of declaration).
 *   - C++20 designated initializers (covered later in this chapter): Employee e {
 *         .firstInitial = 'J', .lastInitial = 'D', .salary = 80'000
 *     }; - omitted members get their in-class default or zero.
 *   - Members can carry in-class default initializers: "int salary { 75'000 };".
 *   - #pragma once (used here) is a widely supported alternative to #ifndef/#define include
 *     guards.
 */

struct Employee {
	char firstInitial;
	char lastInitial;
	int  employeeNumber;
	int  salary;
};
