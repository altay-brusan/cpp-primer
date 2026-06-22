/*
 * Chapter 18 - Writing a Custom Hash Function
 *
 * Unordered (hash-based) containers need a hash function and operator== for
 * their keys. This stores a user-defined IntWrapper in an unordered_set by
 * providing operator== and a std::hash<IntWrapper> specialization whose call
 * operator forwards to the standard hash for int.
 *
 * Key notes:
 *   - Specializing a class template inside namespace std is the sanctioned
 *     exception to the rule against adding to std.
 */

#include <print>
#include <unordered_set>
#include <cstddef>
#include <functional>

using namespace std;

class IntWrapper
{
public:
	explicit IntWrapper(int i) : m_wrappedInt{ i } {}
	int getValue() const { return m_wrappedInt; }
	bool operator==(const IntWrapper&) const = default;// = default since C++20
private:
	int m_wrappedInt;
};

namespace std
{
	template<> struct hash<IntWrapper>
	{
		size_t operator()(const IntWrapper& x) const {
			return std::hash<int>{}(x.getValue());
		}
	};
}

int main()
{
	unordered_set<IntWrapper> s;
	s.insert(IntWrapper{ 1 });
	s.insert(IntWrapper{ 2 });

	for (const auto& element : s) {
		println("{}", element.getValue());
	}
}
