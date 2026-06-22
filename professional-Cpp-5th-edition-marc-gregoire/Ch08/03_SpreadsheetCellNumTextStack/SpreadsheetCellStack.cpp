/*
 * Chapter 8 - Objects on the Stack
 *
 * Two locals get created with their default initialization. One is then driven through the
 * numeric path, the other through the string path. Both are destroyed automatically when
 * main() returns - no manual cleanup, no leaks possible from these two variables.
 *
 * Key notes:
 *   - `SpreadsheetCell myCell, anotherCell;` declares two independent objects, each with
 *     its own `m_value`.
 *   - Use the dot operator on stack objects: `myCell.setValue(6);`.
 *   - A cell's stored value is the parsed double; `getString()` round-trips back to text on
 *     demand.
 */

#include "SpreadsheetCell.h"
#include <print>

using namespace std;

int main()
{
	SpreadsheetCell myCell, anotherCell;
	myCell.setValue(6);
	anotherCell.setString("3.2");

	println("cell 1: {}", myCell.getValue());
	println("cell 2: {}", anotherCell.getValue());

	println("cell 1: {}", myCell.getString());
	println("cell 2: {}", anotherCell.getString());
}
