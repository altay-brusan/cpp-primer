/*
 * Chapter 18 - map Iterators
 *
 * map iterators are bidirectional and refer to key/value pairs, so the value is
 * reached through ->second (or (*iter).second). The example prints the same map
 * four ways: an explicit iterator loop, a range-based for loop, structured
 * bindings, and a const_iterator loop without auto.
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
	dataMap[1] = Data{ 6 }; // Replaces the element with key 1

	// Using auto keyword
	for (auto iter{ cbegin(dataMap) }; iter != cend(dataMap); ++iter) {
		println("{}", iter->second.getValue());
	}

	// Using range-based for loop
	for (const auto& p : dataMap) {
		println("{}", p.second.getValue());
	}

	// Using range-based for loop + structured bindings
	for (const auto& [key, data] : dataMap) {
		println("{}", data.getValue());
	}

	// Using iterators without auto.
	for (map<int, Data>::const_iterator iter{ dataMap.begin() };
		iter != dataMap.end(); ++iter) {
		println("{}", iter->second.getValue());
	}
}
