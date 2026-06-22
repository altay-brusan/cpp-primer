/*
 * Chapter 18 - map::contains()
 *
 * Since C++20, contains() reports whether a key exists in an associative
 * container, returning a bool - clearer than the older count() != 0 idiom.
 * Produces no output.
 */

#include <map>

using namespace std;

class Data final
{
public:
	explicit Data(int value = 0) : m_value{ value } { }
	int getValue() const { return m_value; }
	void setValue(int value) { m_value = value; }

private:
	int m_value;
};

int main()
{
	map<int, Data> dataMap;
	dataMap[1] = Data{ 4 };
	dataMap[1] = Data{ 6 };

	auto isKeyInMap{ dataMap.contains(1) };
}
