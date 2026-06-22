/*
 * Chapter 29 - NameDB Second Attempt Driver (Profiling)
 *
 * Driver identical to the first attempt's, but linked against the map-based NameDB.
 * Re-profiling this build shows the constructor's time collapsing dramatically (the
 * book reports roughly a 67-fold improvement), demonstrating how to verify that an
 * optimization actually helped by profiling before and after.
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
