/*
 * Chapter 1 - DatabaseTest (standalone test for the Database class)
 *
 * Exercises the Database class on its own: add three Employees, fire one, give another a
 * raise, promote a third, then print the all/current/former lists. As with EmployeeTest.cpp,
 * the body of main() is wrapped in a /* ... *\/ block so this file does not collide with
 * UserInterface.cpp for the single main() entry point - leave it commented out unless you
 * are debugging Database in isolation.
 */

#include "Database.h"
#include <print>

using namespace std;
using namespace Records;
/*
int main()
{
	Database myDB;

	Employee& emp1{ myDB.addEmployee("Greg", "Wallis") };
	emp1.fire();

	Employee& emp2{ myDB.addEmployee("Marc", "White") };
	emp2.setSalary(100'000);
	
	Employee& emp3{ myDB.addEmployee("John", "Doe") };
	emp3.setSalary(10'000);
	emp3.promote();
	
	println("All employees:\n==============");
	myDB.displayAll();

	println("\nCurrent employees:\n==================");
	myDB.displayCurrent();

	println("\nFormer employees:\n=================");
	myDB.displayFormer();
}
*/