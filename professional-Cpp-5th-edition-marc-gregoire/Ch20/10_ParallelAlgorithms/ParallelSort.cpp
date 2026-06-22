/*
 * Chapter 20 - Parallel Algorithms (Execution Policies)
 *
 * Demonstrates running a Standard Library algorithm in parallel by passing an
 * execution policy as the first argument. Here std::sort() is invoked with
 * execution::par, allowing the implementation to parallelize the sort. Over 60
 * algorithms accept such policies (seq, par, par_unseq, unseq) from <execution>.
 *
 * Key notes:
 *   - Callbacks passed to parallel algorithms must not throw uncaught exceptions.
 *   - Parallel overloads are not constexpr, even when the serial versions are.
 */

#include <print>
#include <vector>
#include <algorithm>
#include <iostream>
#include <execution>

using namespace std;

// Function template to populate a container of ints.
// A constraint enforces that the container supports push_back(int).
template<typename Container>
	requires requires(Container& c, int i) { c.push_back(i); }
void populateContainer(Container& cont)
{
	while (true) {
		print("Enter a number (0 to stop): ");
		int value;
		cin >> value;
		if (value == 0) {
			break;
		}
		cont.push_back(value);
	}
}

int main()
{
	vector<int> values;
	populateContainer(values);

	println("Before sorting: {:n}", values);
	sort(execution::par, begin(values), end(values));
	println("After sorting: {:n}", values);
}
