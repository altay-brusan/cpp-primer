#pragma once

/*
 * Chapter 1 - The Employee Class (Your First Bigger C++ Program)
 *
 * Employee models one person on the payroll: first/last name, employee number, salary, and
 * hired/fired status. Data members are private; the outside world goes through getters and
 * setters. In-class initializers supply sensible defaults (employee number -1, the
 * DefaultStartingSalary, not hired).
 *
 * Key notes:
 *   - Everything lives in a dedicated namespace, "Records", so names like Employee and
 *     Database do not collide with whatever else the application uses.
 *   - DefaultStartingSalary and DefaultRaiseAndDemeritAmount are namespace-level constants.
 *     They are reached as Records::DefaultRaiseAndDemeritAmount from outside the namespace.
 *   - promote()/demote() declare default arguments tied to DefaultRaiseAndDemeritAmount.
 *     Default values must appear in the declaration (this header), not in the definition.
 *   - Inspectors are marked const: getFirstName() const, isHired() const, display() const.
 *     Anything that just reads state should be const so callers can use const Employee&.
 *   - Strings come in and out as "const std::string&" to avoid copying.
 *   - Returning "const std::string&" from getFirstName() exposes a reference into the
 *     object; callers must not keep the reference past any mutation of the Employee.
 */

#include <string>

namespace Records {
	const int DefaultStartingSalary{ 30'000 };
	const int DefaultRaiseAndDemeritAmount{ 1'000 };

	class Employee
	{
	public:
		Employee(const std::string& firstName, const std::string& lastName);

		void promote(int raiseAmount = DefaultRaiseAndDemeritAmount);
		void demote(int demeritAmount = DefaultRaiseAndDemeritAmount);
		void hire(); // Hires or rehires the employee
		void fire(); // Dismisses the employee
		void display() const; // Prints employee info to console

		// Getters and setters
		void setFirstName(const std::string& firstName);
		const std::string& getFirstName() const;

		void setLastName(const std::string& lastName);
		const std::string& getLastName() const;

		void setEmployeeNumber(int employeeNumber);
		int getEmployeeNumber() const;

		void setSalary(int newSalary);
		int getSalary() const;

		bool isHired() const;

	private:
		std::string m_firstName;
		std::string m_lastName;
		int m_employeeNumber{ -1 };
		int m_salary{ DefaultStartingSalary };
		bool m_hired{ false };
	};
}

