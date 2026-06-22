/*
 * Chapter 9 - Stable Interface via pimpl (driver)
 *
 * Exercises construction with defaults, copy construction, copy assignment, and
 * move assignment. Each public call is a one-line forward into the hidden Impl;
 * the driver does not know - and cannot see - that the Impl exists at all.
 */
#include "Spreadsheet.h"
#include <utility>

using namespace std;

int main()
{
	Spreadsheet s1 { };
	Spreadsheet s2 { 5, 6 };
	Spreadsheet s3 { s2 };
	s1 = s3;
	s1 = move(s3);
}
