/*
 * Chapter 18 - Erasing map Elements by Key
 *
 * Besides erasing by iterator, map offers erase(key) to remove the element with
 * a given key. count(1) (always 0 or 1 for a map) confirms the element is
 * present before and gone after the erase.
 */

#include <print>
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

	println("There are {} elements with key 1.", dataMap.count(1));
	dataMap.erase(1);
	println("There are {} elements with key 1.", dataMap.count(1));
}
