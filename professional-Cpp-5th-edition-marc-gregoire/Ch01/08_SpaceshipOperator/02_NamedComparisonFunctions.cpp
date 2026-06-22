/*
 * Chapter 1 - Three-Way Comparisons (named helpers)
 *
 * <compare> provides named helper functions that turn an ordering result into a bool. They
 * usually read more naturally than comparing against strong_ordering::less and friends.
 *
 * Key notes:
 *   - The helpers: std::is_eq, is_neq, is_lt, is_lteq, is_gt, is_gteq.
 *     They correspond to ==, !=, <, <=, >, >=.
 *   - Each one takes an ordering value (the result of "<=>") and returns a plain bool.
 *   - Useful when the result of "<=>" needs to be stored once and queried in several ways.
 */

#include <print>
#include <compare>

using namespace std;

int main()
{
	int i{ 11 };
	strong_ordering result{ i <=> 0 };
	if (is_lt(result)) { println("less"); }
	if (is_gt(result)) { println("greater"); }
	if (is_eq(result)) { println("equal"); }
}