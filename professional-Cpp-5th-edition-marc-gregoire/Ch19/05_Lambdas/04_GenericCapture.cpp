/*
 * Chapter 19 - Lambda Capture Expressions (Init Captures)
 *
 * Demonstrates lambda capture expressions, which initialize a capture variable with an
 * arbitrary expression rather than copying a same-named variable from scope. The first
 * lambda introduces myCapture = "Pi: " (a variable that does not exist outside) alongside
 * an ordinary by-value capture of pi. The next two move a unique_ptr into the lambda with
 * [p = move(myPtr)] - the only way to capture a move-only type by value - the last reusing
 * the original name (myPtr = move(myPtr)).
 *
 * Key notes:
 *   - Init captures enable capture-by-move, important for non-copyable objects.
 */
#include <print>
#include <memory>
#include <utility>

using namespace std;

int main()
{
	{
		double pi{ 3.1415 };
		auto myLambda{ [myCapture = "Pi: ", pi] { println("{}{}", myCapture, pi); } };
		myLambda();
	}

	{
		auto myPtr{ make_unique<double>(3.1415) };
		auto myLambda{ [p = move(myPtr)] { println("{}", *p); } };
		myLambda();
	}

	{
		auto myPtr{ make_unique<double>(3.1415) };
		auto myLambda{ [myPtr = move(myPtr)] { println("{}", *myPtr); } };
		myLambda();
	}
}
