/*
 * Chapter 16 - Safe Mixed-Sign Integer Comparison with std::cmp_greater
 *
 * Part of the Standard Library tour: this sample shows the C++20 safe integer
 * comparison functions from <utility>. A plain (-1 > 0u) yields true because the
 * signed -1 is implicitly converted to a huge unsigned value before comparison.
 * std::cmp_greater(-1, 0u) instead compares the actual mathematical values and
 * correctly returns false, sidestepping the usual signed/unsigned conversion trap.
 *
 * Key notes:
 *   - The cmp_* family (cmp_equal, cmp_not_equal, cmp_less, cmp_less_equal,
 *     cmp_greater, cmp_greater_equal) is the safe way to compare a signed value
 *     against an unsigned one.
 */

#include <print>
#include <utility>

using namespace std;

int main()
{
	println("{}", (-1 > 0u));            // true
	println("{}", cmp_greater(-1, 0u));  // false
}
