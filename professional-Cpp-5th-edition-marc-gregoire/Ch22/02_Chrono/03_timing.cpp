/*
 * Chapter 22 - Timing Code with steady_clock
 *
 * Measures how long a block of code takes by capturing steady_clock::now() before
 * and after a loop and subtracting the two time_points to obtain a duration. The
 * elapsed time is then expressed in different units: fractional milliseconds via
 * duration<double, milli>, whole milliseconds via duration_cast, and nanoseconds
 * per iteration.
 *
 * Key notes:
 *   - steady_clock is monotonic (it never jumps backward), making it the right
 *     clock for measuring intervals, unlike system_clock.
 *   - The computed result is printed so the optimizer cannot discard the loop.
 */

#include <print>
#include <chrono>
#include <ratio>
#include <cmath>

using namespace std;
using namespace std::chrono;

int main()
{
	// Get the start time.
	auto start{ steady_clock::now() };

	// Execute code that you want to time.
	const int numberOfIterations{ 10'000'000 };
	double d{ 0 };
	for (int i{ 0 }; i < numberOfIterations; ++i) {
		d += sqrt(abs(sin(i) * cos(i)));
	}

	// Get the end time and calculate the difference.
	auto end{ steady_clock::now() };
	auto diff{ end - start };

	// Use the calculated result, otherwise the compiler might
	// optimize away the entire loop!
	println("d = {}", d);

	// Convert the difference into milliseconds and output to the console.
	println("Total: {}", duration<double, milli> { diff });
	// Use duration_cast() if you don't need fractional milliseconds.
	println("Total: {}", duration_cast<milliseconds>(diff));
	// Print the time per iteration in nanoseconds.
	println("{} per iteration", duration<double, nano> { diff / numberOfIterations });
}
