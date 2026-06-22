/*
 * Chapter 18 - Node Handles: extract() and insert()
 *
 * Associative containers are node-based. extract() removes a node from a map
 * and returns a movable node handle that owns the element; insert()-ing that
 * handle into another map transfers the element with no copying or moving.
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

	map<int, Data> dataMap2;
	
	//auto extractedNode{ dataMap.extract(1) };
	//dataMap2.insert(move(extractedNode));
	
	dataMap2.insert(dataMap.extract(1));
}
