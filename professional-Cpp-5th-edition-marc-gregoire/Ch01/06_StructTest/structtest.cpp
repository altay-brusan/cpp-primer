/*
 * Driver for the Employee struct - see employee.h for the conceptual notes.
 *
 * Creates an Employee, assigns each field with the "." operator, and prints the result.
 * Later samples reuse the same struct to motivate uniform initialization
 * ("Employee e { 'J', 'D', 42, 80'000 };") and C++20 designated initializers.
 */

#include <print>
#include "employee.h"

using namespace std;

int main()
{
	// create and populate an employee
	Employee anEmployee;
	anEmployee.firstInitial = 'J';
	anEmployee.lastInitial = 'D';
	anEmployee.employeeNumber = 42;
	anEmployee.salary = 80000;

	// output the values of an employee
	println("Employee: {}{}", anEmployee.firstInitial,
		anEmployee.lastInitial);
	println("Number: {}", anEmployee.employeeNumber);
	println("Salary: ${}", anEmployee.salary);
}
