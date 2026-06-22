/*
 * Chapter 14 - Throwing and Catching a First Exception
 *
 * The minimal try/catch example. safeDivide() uses the throw keyword to throw a
 * std::invalid_argument (from <stdexcept>) when the denominator is zero; main()
 * wraps the calls in a try block and catches it by reference-to-const, printing
 * e.what(). When the exception is thrown, control jumps straight to the catch
 * block, skipping the remaining SafeDivide() calls in the try.
 */

#include <print>
#include <stdexcept>

using namespace std;

double safeDivide(double num, double den)
{
	if (den == 0) {
		throw invalid_argument{ "Divide by zero" };
	}
	return num / den;
}

int main()
{
	try {
		println("{}", safeDivide(5, 2));
		println("{}", safeDivide(10, 0));
		println("{}", safeDivide(3, 3));
	} catch (const invalid_argument& e) {
		println("Caught exception: {}", e.what());
	}
}
