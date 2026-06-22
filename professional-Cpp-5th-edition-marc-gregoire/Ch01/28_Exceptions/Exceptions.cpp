/*
 * Chapter 1 - Exceptions
 *
 * Exceptions report exceptional situations without resorting to sentinel return values.
 * A "throw expr;" terminates the current function immediately, unwinds stack objects, and
 * propagates upward until a matching "catch" handler is found. If none is found anywhere
 * in the call stack, the program calls std::terminate().
 *
 * Key notes:
 *   - Catch by const reference: "catch (const std::invalid_argument& ex)". This avoids
 *     slicing (catching a base type by value drops the derived parts) and unnecessary copies.
 *   - All Standard Library exception types derive from std::exception and provide
 *     "const char* what() const noexcept" with an error message.
 *   - Common standard exceptions live in <stdexcept>: std::logic_error, std::runtime_error,
 *     std::invalid_argument, std::out_of_range, std::overflow_error, etc.
 *   - Catch from most-derived to least-derived. A "catch (const std::exception&)" handler
 *     is a useful last-resort fallback.
 *   - Throwing pointers is bad practice (who deletes?); throw objects.
 *   - Mark functions "noexcept" when they never throw - it can enable optimizations.
 *   - Stack unwinding destroys all local objects properly. RAII types (smart pointers,
 *     vectors, file handles) release their resources during unwinding.
 *   - Chapter 14 covers exception handling in depth, including writing custom exception
 *     types.
 */

#include <print>
#include <stdexcept>

using namespace std;

double divideNumbers(double numerator, double denominator)
{
	if (denominator == 0) {
		throw invalid_argument{ "Denominator cannot be 0." };
	}
	return numerator / denominator;
}

int main()
{
	try {
		println("{}", divideNumbers(2.5, 0.5));
		println("{}", divideNumbers(2.3, 0));
		println("{}", divideNumbers(4.5, 2.5));
	} catch (const invalid_argument& exception) {
		println("Exception caught: {}", exception.what());
	}
}
