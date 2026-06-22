/*
 * Chapter 32 - Writing a Lambda Expression (syntax refresher)
 *
 * Demonstrates a lambda expression used together with a Standard Library algorithm.
 * ranges::count_if() counts the even values in a vector, and the lambda additionally
 * captures callCount by reference ([&callCount]) so it can record how many times it is
 * invoked, illustrating how lambdas can carry state from their enclosing scope.
 *
 * Key notes:
 *   - Capturing by reference lets the lambda modify a variable in the outer scope.
 */
#include <print>
#include <vector>
#include <ranges>
#include <algorithm>

using namespace std;

int main()
{
	vector values{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	int callCount{ 0 };

	auto evenCount{ranges::count_if(values,
		[&callCount](int value) {
			++callCount; 
			return value % 2 == 0;
		})
	};

	println("There are {} even elements in the vector.", evenCount);
	println("Lambda was called {} times.", callCount);
}