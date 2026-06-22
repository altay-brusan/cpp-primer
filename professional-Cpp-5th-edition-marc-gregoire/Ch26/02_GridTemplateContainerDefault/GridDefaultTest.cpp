/*
 * Chapter 26 - Relying on a Default Template Argument
 *
 * Shows that Grid<int> compiles by falling back to the default container
 * argument (vector<optional<int>>), while an explicit deque or vector can
 * still be supplied when desired.
 */

#include "GridDefault.h"
#include <vector>
#include <deque>

using namespace std;

int main()
{
	Grid<int, deque<optional<int>>> myDequeGrid;
	Grid<int, vector<optional<int>>> myVectorGrid;
	Grid<int> myVectorGrid2{ myVectorGrid };
}
