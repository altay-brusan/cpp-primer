/*
 * Chapter 18 - The std::erase() Non-Member Function
 *
 * Since C++20, std::erase(container, value) removes all elements equal to a
 * value in a single linear-time call, avoiding the older quadratic
 * erase-in-a-loop approach. A companion std::erase_if() takes a predicate.
 */

#include <print>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	vector values{ 1, 2, 3, 2, 1, 2, 4, 5 };
	println("{:n}", values);

	erase(values, 2);  // Removes all values equal to 2.
	println("{:n}", values);
}
