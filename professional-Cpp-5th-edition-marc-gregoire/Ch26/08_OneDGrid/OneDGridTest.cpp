/*
 * Chapter 26 - Nesting OneDGrid to Reach Higher Dimensions
 *
 * Declares one-, two-, and three-dimensional grids by manually nesting
 * OneDGrid inside OneDGrid, showing both that the technique works and how
 * unwieldy the nested type names become.
 */

#include "OneDGrid.h"

int main()
{
	OneDGrid<int> singleDGrid;
	OneDGrid<OneDGrid<int>> twoDGrid;
	OneDGrid<OneDGrid<OneDGrid<int>>> threeDGrid;

	singleDGrid[3] = 5;
	twoDGrid[3][3] = 5;
	threeDGrid[3][3][3] = 5;
}
