/*
 * Chapter 18 - Reclaiming vector Memory
 *
 * A vector never shrinks its capacity on its own. The swap-with-a-temporary
 * trick, vector<int>().swap(values), hands all of values' memory to an empty
 * temporary that is destroyed at the end of the statement, leaving values with
 * zero capacity. Produces no output.
 */

#include <vector>

using namespace std;

int main()
{
	vector<int> values;
	// Populate values ...
	vector<int>().swap(values);
}
