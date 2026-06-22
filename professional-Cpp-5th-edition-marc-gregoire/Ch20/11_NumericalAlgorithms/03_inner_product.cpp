/*
 * Chapter 20 - The inner_product Algorithm
 *
 * Demonstrates std::inner_product() from <numeric>, which combines two ranges
 * pairwise. By default it multiplies corresponding elements and sums the products;
 * for {1,2,3,4} and {9,8,7,6} the result is (1*9)+(2*8)+(3*7)+(4*6) = 70.
 *
 * Key notes:
 *   - inner_product() is not parallelizable; use transform_reduce() if needed.
 */

#include <print>
#include <vector>
#include <numeric>

using namespace std;

int main()
{
	vector v1{ 1, 2, 3, 4 };
	vector v2{ 9, 8, 7, 6 };
	println("{}", inner_product(cbegin(v1), cend(v1), cbegin(v2), 0));
}
