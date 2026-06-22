/*
 * Chapter 11 - Modules (4/10): Implementation Unit
 *
 * `module person;` (no `export` here) marks this file as an *implementation
 * unit* of the `person` module. It inherits the module's exports and can
 * see private interface declarations.
 *
 * Note that the implementation unit doesn't need to import `std` again,
 * because the interface unit already did.
 */
module person;

using namespace std;

Person::Person(string firstName, string lastName)
	: m_firstName{ move(firstName) }, m_lastName{ move(lastName) }
{
}

const string& Person::getFirstName() const
{
	return m_firstName;
}

const string& Person::getLastName() const
{
	return m_lastName;
}
