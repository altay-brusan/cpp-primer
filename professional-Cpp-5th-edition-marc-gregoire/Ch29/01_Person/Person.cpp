/*
 * Chapter 29 - Pass-by-Value vs Pass-by-Reference (Handling Objects Efficiently)
 *
 * Demonstrates the copying cost of passing objects by value versus by
 * reference-to-const. The Person class prints from each special member function so
 * you can watch exactly which constructors, copy constructors, and destructors fire.
 * The constructor takes its string parameters by value and moves them into the data
 * members, the idiom recommended when a function would copy anyway. processPerson()
 * is shown here taking the argument by const reference (the by-value version is kept
 * commented out for comparison), avoiding the extra copy and destructor calls that a
 * by-value Person parameter would incur for its two string members.
 *
 * Key notes:
 *   - Prefer reference-to-const for types that do not benefit from move semantics;
 *     prefer pass-by-value plus move for parameters the function would copy anyway.
 *   - Run it and count the printed lines to see how many copies by-value would add.
 */

#include <print>
#include <string>
#include <iostream>
#include <utility>

using namespace std;

class Person
{
public:
	Person();
	explicit Person(string firstName, string lastName, int age);
	Person(const Person& rhs);
	virtual ~Person();

	const string& getFirstName() const { return m_firstName; }
	const string& getLastName() const { return m_lastName; }
	int getAge() const { return m_age; }

private:
	string m_firstName, m_lastName;
	int m_age{ 0 };
};

Person::Person()
{
	println("Default Ctor");
}

Person::Person(string firstName, string lastName, int age)
	: m_firstName{ move(firstName) }, m_lastName{ move(lastName) }, m_age{ age }
{
	println("Ctor");
}

Person::~Person()
{
	println("Dtor");
}

Person::Person(const Person& rhs)
	: m_firstName{ rhs.m_firstName }, m_lastName{ rhs.m_lastName }, m_age{ rhs.m_age }
{
	println("Copy ctor");
}

ostream& operator<<(ostream& ostr, const Person& p)
{
	ostr << p.getFirstName() << " " << p.getLastName() <<
		" " << p.getAge() << endl;

	return ostr;
}


/*
void processPerson(Person p)
{
// process the person
}
*/


void processPerson(const Person& /*p*/)
{
	// process the person
}

int main()
{
	Person me{ "Marc", "Gregoire", 42 };
	processPerson(me);
}

