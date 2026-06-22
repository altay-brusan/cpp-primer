/*
 * Chapter 11 - Modules (4/10): Interface + Implementation Files
 *
 * The .cppm declares the class - this is the *primary module interface
 * unit*. Bodies for the member functions live in Person.cpp, which is a
 * *module implementation unit* (note: `module person;` without `export` at
 * the top).
 *
 * Key notes:
 *   - The split mirrors the traditional header/.cpp pattern, but compiled
 *     once per module instead of once per translation unit that includes
 *     the header. That's where modules' compile-time win comes from.
 *   - Importers don't see the implementation unit; they only see this .cppm.
 */
export module person;

import std;

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
