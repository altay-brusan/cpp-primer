/*
 * Chapter 18 - map operator[]
 *
 * operator[] inserts or replaces by key with a simple syntax. Unlike insert(),
 * it always succeeds and overwrites any existing value, but it
 * default-constructs a value when the key is absent. Produces no output.
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
	dataMap[1] = Data{ 6 }; // Replaces the element with key 1
}
