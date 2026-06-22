/*
 * Chapter 22 - Time Points
 *
 * Demonstrates std::chrono::time_point, which represents a point in time as a
 * duration measured from a clock's epoch. A default-constructed time_point sits at
 * the epoch; here minutes are added to it, and time_since_epoch() retrieves the
 * stored duration, which is then converted to seconds for output.
 *
 * Key notes:
 *   - A time_point is parameterized by both its clock and the duration type used
 *     to count from the epoch.
 */

#include <print>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main()
{
	// Create a time_point representing the epoch of the associated steady clock.
	time_point<steady_clock> tp1;
	// or
	// steady_clock::time_point tp1;

	// Add 10 minutes to the time_point.
	tp1 += minutes{ 10 };
	
	// Store the duration between epoch and time_point.
	auto d1{ tp1.time_since_epoch() };
	
	// Convert the duration to seconds and output to the console.
	duration<double> d2{ d1 };
	println("{}", d2);
}
