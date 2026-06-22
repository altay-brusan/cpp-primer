/*
 * Chapter 29 - NameDB First Attempt Driver (Profiling)
 *
 * Driver that builds the vector-based NameDB from boys_long.txt (about 500,500 names)
 * and prints the ranks of a few names. This is the program you run under a profiler
 * such as gprof or the Visual C++ profiler to confirm that the NameDB constructor, and
 * specifically the linear searches inside it, dominate the run time.
 *
 * Key notes:
 *   - Needs the data file boys_long.txt in the working directory to run.
 *   - Link this driver together with NameDB.cpp; neither runs on its own.
 */

#include "NameDB.h"
#include <print>

using namespace std;

int main()
{
	NameDB boys{ "boys_long.txt" };

	println("{}", boys.getNameRank("Daniel"));
	println("{}", boys.getNameRank("Jacob"));
	println("{}", boys.getNameRank("William"));
}
