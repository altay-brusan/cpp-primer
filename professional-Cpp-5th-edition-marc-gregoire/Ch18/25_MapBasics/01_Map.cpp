/*
 * Chapter 18 - Constructing a map
 *
 * std::map stores sorted key/value pairs. This creates an empty
 * map<int, Data> mapping int keys to objects of a user-defined Data class;
 * internally each element is a pair<const int, Data>. Produces no output.
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
}
