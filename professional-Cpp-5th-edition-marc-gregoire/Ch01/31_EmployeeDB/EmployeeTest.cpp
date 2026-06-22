/*
 * Chapter 1 - EmployeeTest (standalone test for the Employee class)
 *
 * Each class is easier to debug when you exercise it in isolation before wiring it into the
 * bigger program. This file is that isolated test. Because a program can only have one
 * main(), the body of main() below is wrapped in a /* ... *\/ block comment so this file
 * does not fight with UserInterface.cpp for the entry point. Leave it commented out unless
 * you are debugging Employee on its own.
 *
 * Key notes:
 *   - Unit-testing frameworks (gtest, Catch2) are the production-grade version of this idea.
 *     Chapter 30 covers them.
 *   - When you have multiple .cpp files each defining main(), the linker reports "multiple
 *     definition of main" - that is the symptom of forgetting to comment out a test driver.
 */

#include "Employee.h"
#include <print>

using namespace std;
using namespace Records;
/*
int main()
{
	println("Testing the Employee class.");

	Employee emp{ "Jane", "Doe" };
	emp.setFirstName("John");
	emp.setLastName("Doe");
	emp.setEmployeeNumber(71);
	emp.setSalary(50'000);
	emp.promote();
	emp.promote(50);
	emp.hire();
	emp.display();
}
*/