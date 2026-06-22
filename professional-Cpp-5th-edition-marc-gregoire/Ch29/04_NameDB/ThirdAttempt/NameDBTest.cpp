/*
 * Chapter 29 - NameDB Third Attempt Driver (Profiling)
 *
 * Driver identical to the earlier attempts', linked against the streamlined map-based
 * NameDB. It builds the database from boys_long.txt and prints a few name ranks,
 * letting you confirm that the simplified constructor behaves the same while doing
 * less work per name.
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
