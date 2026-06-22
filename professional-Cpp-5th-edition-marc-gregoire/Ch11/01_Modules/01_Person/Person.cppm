/*
 * Chapter 11 - Modules (1/10): A Single-File Module Interface
 *
 * NOTE: This is the "No Modules" edition of the book examples, but the
 * Modules sub-directory keeps the original module sources for reference.
 * To actually build these files you need a modules-capable compiler:
 *   - MSVC:   cl /std:c++latest /interface /TP Person.cppm + test.cpp
 *   - Clang:  clang++ --precompile -std=c++23 Person.cppm -o person.pcm,
 *             then compile test.cpp with -fmodule-file=person.pcm
 *   - GCC 14+ (with -fmodules-ts) is similar.
 *
 * What the file demonstrates:
 *   - `export module person;` opens a *named module* called "person".
 *   - `import std;` is the new way to pull in the entire Standard Library
 *     (faster than `#include <...>` once compiled).
 *   - `export class Person` makes the class visible to importers; anything
 *     without `export` is private to this module.
 *   - Both the class definition and its inline member functions sit in the
 *     same .cppm. Separating them is shown in samples 04 and 05.
 */
export module person;

import std;

export class Person
{
public:
	explicit Person(std::string firstName, std::string lastName)
		: m_firstName{ std::move(firstName) }, m_lastName{ std::move(lastName) } { }

	const std::string& getFirstName() const { return m_firstName; }
	const std::string& getLastName() const { return m_lastName; }

private:
	std::string m_firstName;
	std::string m_lastName;
};
