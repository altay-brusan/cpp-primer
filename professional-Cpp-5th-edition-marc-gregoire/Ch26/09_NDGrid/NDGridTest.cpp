/*
 * Chapter 26 - Using the Recursive N-Dimensional Grid
 *
 * Creates a 3-D grid as NDGrid<int, 3> with a chosen size, then indexes it with
 * chained operator[] calls, demonstrating the clean syntax that the template
 * recursion enables compared with manual nesting.
 */

#include "NDGrid.h"
#include <print>

using namespace std;

int main()
{
	NDGrid<int, 3> my3DGrid{ 4 };
	my3DGrid[2][1][2] = 5;
	my3DGrid[1][1][1] = 5;

	println("{}", my3DGrid[2][1][2]);
}
