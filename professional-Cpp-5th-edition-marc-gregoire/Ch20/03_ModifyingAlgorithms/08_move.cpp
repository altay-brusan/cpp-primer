/*
 * Chapter 20 - The move Algorithm and Move Semantics
 *
 * Demonstrates the std::move() algorithm (three-iterator overload) that moves
 * elements from a source range to a destination using move assignment. MyClass
 * provides a noexcept move assignment operator that the algorithm invokes; the
 * print output confirms moves rather than copies are used.
 *
 * Key notes:
 *   - The three-argument move() (the algorithm) differs from the single-argument
 *     std::move() in <utility> that just casts an lvalue to an rvalue.
 *   - After the move, the source elements are in a valid but unspecified state.
 */

#include <print>
#include <vector>
#include <algorithm>
#include <string>
#include <utility>

using namespace std;

class MyClass
{
public:
	MyClass() = default;
	MyClass(const MyClass& src) = default;
	explicit MyClass(string str) : m_str{ move(str) } {}
	virtual ~MyClass() = default;
	
	// Move assignment operator
	MyClass& operator=(MyClass&& rhs) noexcept {
		if (this == &rhs) { return *this; }
		m_str = move(rhs.m_str);
		println("Move operator= (m_str={})", m_str);
		return *this;
	}
	
	void setString(string str) { m_str = move(str); }
	const string& getString() const { return m_str; }

private:
	string m_str;
};

int main()
{
	vector<MyClass> vecSrc{ MyClass { "a" }, MyClass { "b" }, MyClass { "c" } };
	vector<MyClass> vecDst(vecSrc.size());
	move(begin(vecSrc), end(vecSrc), begin(vecDst));
	for (const auto& c : vecDst) { print("{} ", c.getString()); }
}
