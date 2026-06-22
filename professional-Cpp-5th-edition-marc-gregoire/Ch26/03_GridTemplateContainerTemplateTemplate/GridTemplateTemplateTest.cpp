/*
 * Chapter 26 - Passing a Container Template as an Argument
 *
 * Demonstrates the template template parameter Grid by instantiating it as
 * Grid<int, vector> and Grid<int, deque>, passing the bare container template
 * name rather than a concrete container type.
 */

#include "GridTemplateTemplate.h"
#include <print>
#include <vector>
#include <deque>

using namespace std;

int main()
{
	Grid<int, vector> myGrid;
	myGrid.at(1, 2) = 3;
	println("{}", myGrid.at(1, 2).value_or(0));

	Grid<int, vector> myGrid2{ myGrid };

	Grid<int, deque> myDequeGrid;
}
