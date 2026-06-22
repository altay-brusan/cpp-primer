/*
 * Chapter 20 - for_each Accumulating via Captured References
 *
 * Uses std::for_each() with a lambda that captures sum and product by reference to
 * compute both the sum and the product of a range in a single pass. Capturing by
 * reference is required so the updates remain visible after the algorithm returns.
 */

#include <print>
#include <vector>
#include <algorithm>
#include <iostream>

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
	vector<int> myVector;
	populateContainer(myVector);

	int sum{ 0 };
	int product{ 1 };
	for_each(cbegin(myVector), cend(myVector),
		[&sum, &product](int i){
			sum += i;
			product *= i;
	});
	println("The sum is {}", sum);
	println("The product is {}", product);
}
