/*
 * Chapter 20 - The iota Numeric Algorithm
 *
 * Demonstrates std::iota() from <numeric>, which fills a range with successively
 * increasing values starting from a given seed by repeatedly applying operator++.
 * Here a 10-element vector is filled with 5, 6, 7, ... 14.
 */

#include <print>
#include <vector>
#include <numeric>

using namespace std;

int main()
{
	vector<int> values(10);
	iota(begin(values), end(values), 5);
	println("{:n}", values);
}