/*
 * Chapter 11 - Modules (5/10): One File, Two Halves
 *
 * Same module as sample 04, but the implementations live in the SAME .cppm
 * file - just below the class declaration. Anything that's not marked
 * `export` (including the out-of-class function definitions) stays internal
 * to the module.
 *
 * Key notes:
 *   - This is a halfway point between "everything inline in the header"
 *     (sample 01) and "interface + implementation unit" (sample 04).
 *   - The benefit: smaller class definition (just declarations), but no
 *     separate compilation unit to manage.
 */
export module person;

import std;

// Class definition
export class Person
{
public:
	explicit Person(std::string firstName, std::string lastName);

	const std::string& getFirstName() const;
	const std::string& getLastName() const;

private:
	std::string m_firstName;
	std::string m_lastName;
};

// Implementations - not exported; clients only see the declarations above.
Person::Person(std::string firstName, std::string lastName)
	: m_firstName{ std::move(firstName) }, m_lastName{ std::move(lastName) }
{
}

const std::string& Person::getFirstName() const
{
	return m_firstName;
}

const std::string& Person::getLastName() const
{
	return m_lastName;
}
