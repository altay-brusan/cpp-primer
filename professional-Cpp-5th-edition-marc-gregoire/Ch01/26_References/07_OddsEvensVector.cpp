/*
 * Chapter 1 - Deciding Between References and Pointers (vector version)
 *
 * Switching to std::vector deletes every memory-management bug in one step. The input
 * vector is passed as "const vector<int>&" (cheap, read-only), the outputs as
 * "vector<int>&" so the function can push_back into them. No new/delete, no sizes to track,
 * no risk of leaks or double frees.
 *
 * Key notes:
 *   - vector knows its own size; the function does not need extra size parameters.
 *   - Range-based for ("for (int i : arr)") iterates the input cleanly.
 *   - Caller does not delete anything - the vector's destructor releases the storage.
 *   - Prefer Standard Library containers over raw dynamic arrays in essentially all new code.
 *   - The output-parameter style still has a downside: the caller must construct the result
 *     vectors and remember to pass them in. Sample 08 fixes that by returning a struct.
 */

#include <print>
#include <vector>

using namespace std;

void printVec(const vector<int>& arr)
{
	for (int i : arr) {
		print("{} ", i);
	}
	println("");
} 

void separateOddsAndEvens(const vector<int>& arr,
						  vector<int>& odds, vector<int>& evens)
{
	for (int i : arr) {
		if (i % 2 == 0) {
			evens.push_back(i);
		} else {
			odds.push_back(i);
		}
	}
}

int main()
{
	vector<int> vecUnSplit{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -1, -2};
	vector<int> odds, evens;

	separateOddsAndEvens(vecUnSplit, odds, evens);

	printVec(odds);
	printVec(evens);
}
