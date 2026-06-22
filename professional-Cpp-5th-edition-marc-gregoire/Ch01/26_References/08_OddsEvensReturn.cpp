/*
 * Chapter 1 - Avoid output parameters; just return by value
 *
 * Final iteration of the running example. Instead of taking two output vectors, the function
 * bundles them into an OddsAndEvens struct and returns it. The return statement uses C++20
 * designated initializers so the call site reads which member receives which value.
 *
 * Key notes:
 *   - Returning by value is as fast as it looks: compilers apply Return Value Optimization
 *     (RVO) and Named Return Value Optimization (NRVO), forms of copy elision that
 *     construct the result directly in the caller's slot - zero copies.
 *   - Rule of thumb: if a function needs to produce a result, return it. Reach for output
 *     parameters only for niche cases (multiple results that the caller must reuse, etc.).
 *   - Returning a struct of multiple results pairs nicely with structured bindings at the
 *     call site: "auto [odds, evens] = separateOddsAndEvens(input);" if the struct's
 *     members are public (as in an aggregate).
 *   - Designated initializers ".odds = odds, .evens = evens" require member names to appear
 *     in declaration order.
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

struct OddsAndEvens { vector<int> odds, evens; };

OddsAndEvens separateOddsAndEvens(const vector<int>& arr)
{
	vector<int> odds, evens;
	for (int i : arr) {
		if (i % 2 == 0) {
			evens.push_back(i);
		} else {
			odds.push_back(i);
		}
	}
	return OddsAndEvens{ .odds = odds, .evens = evens };
}

int main()
{
	vector<int> vecUnSplit{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -1, -2};
	auto oddsAndEvens{ separateOddsAndEvens(vecUnSplit) };
	printVec(oddsAndEvens.odds);
	printVec(oddsAndEvens.evens);
}
