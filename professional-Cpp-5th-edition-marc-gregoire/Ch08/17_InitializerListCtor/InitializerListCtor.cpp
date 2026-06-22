/*
 * Chapter 8 - Initializer-List Constructors
 *
 * An initializer-list constructor takes a single `std::initializer_list<T>` parameter
 * (possibly followed by parameters with defaults). When a caller writes a brace-enclosed
 * list - `EvenSequence p { 1.0, 2.0, 3.0, 4.0 }` - and the class has such a constructor,
 * overload resolution prefers it over any other constructor that could also match the
 * braces. That is how the standard containers can accept `{a, b, c}` directly.
 *
 * Key notes:
 *   - Signature pattern: `Class(std::initializer_list<T>);` - declared in
 *     `<initializer_list>`.
 *   - Iterate the list with a range-based for; `size()` returns the element count.
 *   - Throwing from a constructor is fine - the partially-built object is rolled back and
 *     no destructor runs for it.
 *   - `vector<string> v { "a", "b" };` uses the same mechanism inside the standard
 *     library.
 *   - When a class has both an initializer-list ctor and a normal multi-arg ctor, brace
 *     initialization will pick the initializer-list ctor first, which is occasionally
 *     surprising - know your overload set.
 *
 * Example:
 *     // The body could be one line via vector's own initializer-list-aware assign:
 *     // m_sequence.assign(values);
 */

#include <print>
#include <initializer_list>
#include <stdexcept>
#include <vector>

using namespace std;

class EvenSequence
{
public:
	EvenSequence(initializer_list<double> values)
	{
		if (values.size() % 2 != 0) {
			throw invalid_argument{ "initializer_list should "
				"contain even number of elements." };
		}

		m_sequence.reserve(values.size());
		for (const auto& value : values) {
			m_sequence.push_back(value);
		}
		
		// Or:
		// m_sequence.assign(values);
	}

	void print() const
	{
		for (const auto& value : m_sequence) {
			std::print("{}, ", value);
		}
		println("");
	}
private:
	vector<double> m_sequence;
};

int main()
{
	try {
		EvenSequence p1{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
		p1.print();

		EvenSequence p2 { 1.0, 2.0, 3.0 };
	} catch (const invalid_argument& e) {
		println("{}", e.what());
	}
}