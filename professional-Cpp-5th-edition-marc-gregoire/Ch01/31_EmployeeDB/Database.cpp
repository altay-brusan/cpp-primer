/*
 * Implementation for Database.h - see the header for the conceptual notes.
 *
 * Worth noting:
 *   - addEmployee() builds a local Employee, sets its number with the post-increment
 *     (m_nextEmployeeNumber++ returns the current value, THEN increments), hires it, and
 *     push_back()-es it. Returning m_employees.back() yields a reference to the stored
 *     copy, not to the local.
 *   - Both getEmployee() overloads iterate with "for (auto& e : m_employees)" so they can
 *     return a non-const reference to the match. When no match is found they throw
 *     std::logic_error - which the UserInterface code catches.
 *   - The display* loops use "for (const auto& e : ...)" because they only read.
 */

#include "Database.h"
#include <stdexcept>

using namespace std;

namespace Records {

	Employee& Database::addEmployee(const string& firstName,
		const string& lastName)
	{
		Employee theEmployee{ firstName, lastName };
		theEmployee.setEmployeeNumber(m_nextEmployeeNumber++);
		theEmployee.hire();
		m_employees.push_back(theEmployee);

		return m_employees.back();
	}

	Employee& Database::getEmployee(int employeeNumber)
	{
		for (auto& employee : m_employees) {
			if (employee.getEmployeeNumber() == employeeNumber) {
				return employee;
			}
		}
		throw logic_error{ "No employee found." };
	}

	Employee& Database::getEmployee(const string& firstName, const string& lastName)
	{
		for (auto& employee : m_employees) {
			if (employee.getFirstName() == firstName &&
				employee.getLastName() == lastName) {
					return employee;
			}
		}
		throw logic_error{ "No employee found." };
	}

	void Database::displayAll() const
	{
		for (const auto& employee : m_employees) {
			employee.display();
		}
	}

	void Database::displayCurrent() const
	{
		for (const auto& employee : m_employees) {
			if (employee.isHired()) {
				employee.display();
			}
		}
	}

	void Database::displayFormer() const
	{
		for (const auto& employee : m_employees) {
			if (!employee.isHired()) {
				employee.display();
			}
		}
	}

}
