#pragma once

/*
 * Chapter 1 - The Database Class (Your First Bigger C++ Program)
 *
 * Database is the central store for Employee records. It owns a std::vector<Employee> and an
 * internal counter that auto-assigns each new employee a unique id starting at
 * FirstEmployeeNumber. addEmployee() returns a reference to the freshly added Employee so
 * the caller can keep working with it directly.
 *
 * Key notes:
 *   - The two getEmployee() overloads differ only in their parameter list (int vs two
 *     strings). The compiler picks the right one from the arguments at the call site.
 *   - Returning "Employee&" exposes the stored object - the caller can mutate it. To force
 *     read-only access, the API would return "const Employee&" instead.
 *   - The display* methods are marked const: they only read state. Const inspectors can be
 *     called on a const Database.
 *   - Holding Employee objects by value in the vector keeps memory management trivial - the
 *     vector destructor releases them all. References returned by addEmployee()/getEmployee()
 *     can be invalidated by later push_back() if the vector reallocates.
 */

#include "Employee.h"
#include <string>
#include <vector>

namespace Records {
	const int FirstEmployeeNumber{ 1'000 };

	class Database
	{
	public:
		Employee& addEmployee(const std::string& firstName,
							  const std::string& lastName);
		Employee& getEmployee(int employeeNumber);
		Employee& getEmployee(const std::string& firstName,
							  const std::string& lastName);

		void displayAll() const;
		void displayCurrent() const;
		void displayFormer() const;

	private:
		std::vector<Employee> m_employees;
		int m_nextEmployeeNumber{ FirstEmployeeNumber };
	};
}
