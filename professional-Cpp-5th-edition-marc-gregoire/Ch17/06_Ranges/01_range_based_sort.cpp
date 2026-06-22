/*
 * Chapter 17 - Range-Based Algorithms and Projections
 *
 * Contrasts the iterator-pair std::sort(begin, end) with the C++20
 * std::ranges::sort(data), which takes a whole range and so cannot be given
 * mismatched iterators. It then introduces projections: since Person has no
 * operator<, ranges::sort is called with a default comparator {} and a projection
 * (&Person::getFirstName) that maps each Person to the field used for comparison,
 * sorting the vector by first name. A commented lambda shows the equivalent
 * projection written explicitly.
 */

#include <print>
#include <vector>
#include <ranges>
#include <algorithm>
#include <string>
#include <utility>

using namespace std;

class Person
{
public:
	explicit Person(string first, string last)
		: m_firstName{ move(first) }, m_lastName{ move(last) } { }

	const string& getFirstName() const { return m_firstName; }
	const string& getLastName() const { return m_lastName; }

private:
	string m_firstName;
	string m_lastName;
};

int main()
{
	vector data{ 33, 11, 22 };
	sort(begin(data), end(data));
	ranges::sort(data);



	vector persons{ Person{"John", "White"}, Person{"Chris", "Blue"} };

	//sort(begin(persons), end(persons)); // Error: does not compile.
	//ranges::sort(persons); // Error: does not compile.

	//ranges::sort(persons, {},
	//	[](const Person& person) { return person.getFirstName(); });
	// Or:
	ranges::sort(persons, {}, &Person::getFirstName);
	
	for (const auto& person : persons) { println("{}", person.getFirstName()); }
}
