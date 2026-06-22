/*
 * Chapter 20 - The clamp Algorithm
 *
 * Demonstrates std::clamp(v, lo, hi), which constrains a value to a range: it
 * returns lo if v < lo, hi if v > hi, and otherwise v itself. The three calls show
 * a value below, within, and above the [1, 10] bounds.
 */

#include <print>
#include <algorithm>

using namespace std;

int main()
{
	println("{}", clamp(-3, 1, 10));
	println("{}", clamp(3, 1, 10));
	println("{}", clamp(22, 1, 10));
}
