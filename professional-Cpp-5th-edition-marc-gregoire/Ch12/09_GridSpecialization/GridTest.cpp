/*
 * Chapter 12 - Template Specialization: driver
 *
 * `Grid<int>` resolves to the primary template.
 * `Grid<const char*>` resolves to the specialization in GridString.h.
 *
 * The caller writes `stringGrid.at(0,0) = "hello"`, but inside the cell
 * a `std::string` is constructed and stored - that's why the deep copy
 * via `Grid<const char*> stringGrid2{stringGrid1}` works without any
 * dangling-pointer concerns.
 */
#include "Grid.h"
#include "GridString.h"
#include <print>

using namespace std;

int main()
{
	Grid<int> myIntGrid;					// Uses original Grid template.
	Grid<const char*> stringGrid1{ 2, 2 };	// Uses const char* specialization.

	const char* dummy{ "dummy" };
	stringGrid1.at(0, 0) = "hello";
	stringGrid1.at(0, 1) = dummy;
	stringGrid1.at(1, 0) = dummy;
	stringGrid1.at(1, 1) = "there";

	Grid<const char*> stringGrid2{ stringGrid1 };

	println("{}", stringGrid1.at(0, 1).value_or(""));
	println("{}", stringGrid2.at(0, 1).value_or(""));
}
