/*
 * Chapter 12 - Default Template Arguments: driver
 *
 * Four spellings, all valid:
 *   - `Grid<>`         - all three defaults: int, 10, 10.
 *   - `Grid<int>`      - explicit T, default WIDTH/HEIGHT.
 *   - `Grid<int, 5>`   - default HEIGHT only.
 *   - `Grid<int,5,5>`  - everything explicit.
 *
 * Note that `Grid<>` requires the angle brackets - bare `Grid` is the
 * *template name*, not a type.
 */
#include "Grid.h"

using namespace std;

int main()
{
	Grid<> myIntGrid;
	Grid<int> myGrid;
	Grid<int, 5> anotherGrid;
	Grid<int, 5, 5> aFourthGrid;
}
