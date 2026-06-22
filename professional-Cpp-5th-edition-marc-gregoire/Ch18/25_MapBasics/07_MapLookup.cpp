/*
 * Chapter 18 - Looking Up map Elements
 *
 * Three ways to reach a value by key: operator[] (which would insert if the key
 * were missing), find() returning an iterator you compare against end(), and
 * at() which throws out_of_range on a missing key. Produces no output.
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
	dataMap[1].setValue(100);

	auto it{ dataMap.find(1) };
	if (it != end(dataMap)) {
		it->second.setValue(100);
	}

	dataMap.at(1).setValue(200);
}
