/*
 * Chapter 22 - Converting the Precision of Time Points
 *
 * Shows how a time_point's underlying duration precision can be changed. Going to
 * a finer precision (seconds to milliseconds) is implicit because no information is
 * lost, while going to a coarser precision (milliseconds to seconds) requires an
 * explicit time_point_cast, which truncates toward zero.
 *
 * Key notes:
 *   - time_point_cast is the time_point analogue of duration_cast.
 */

#include <print>
#include <chrono>


using namespace std;
using namespace std::chrono;

int main()
{
	{
		time_point<steady_clock, seconds> tpSeconds{ 42s };
		// Convert seconds to milliseconds implicitly.
		time_point<steady_clock, milliseconds> tpMilliseconds{ tpSeconds };

		println("{}", tpMilliseconds.time_since_epoch());
	}

	{
		time_point<steady_clock, milliseconds> tpMilliseconds{ 42'424ms };
		// Convert milliseconds to seconds explicitly.
		time_point<steady_clock, seconds> tpSeconds{
			time_point_cast<seconds>(tpMilliseconds) };
		// Or:
		//auto tpSeconds{ time_point_cast<seconds>(tpMilliseconds) };

		// Convert seconds back to milliseconds and output the result.
		milliseconds ms{ tpSeconds.time_since_epoch() };
		println("{}", ms);
	}
}
