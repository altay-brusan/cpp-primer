/*
 * Chapter 8 - Delegating constructor in action
 *
 * Constructing with a string runs the string_view constructor, which immediately delegates
 * to the double constructor. By the time control reaches the (empty) body of the
 * delegating constructor, `m_value` is already set.
 */

#include "SpreadsheetCell.h"
#include <print>

using namespace std;

int main()
{
	SpreadsheetCell myCell{ "6.2" };
	println("cell 1: {}", myCell.getValue());
}
