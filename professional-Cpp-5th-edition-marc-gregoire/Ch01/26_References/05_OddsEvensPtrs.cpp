/*
 * Chapter 1 - Deciding Between References and Pointers (pointer version)
 *
 * separateOddsAndEvens() needs to write into four caller-owned values (two array pointers
 * and two sizes). Doing it the C way: each output is a pointer that the function dereferences
 * to update the caller's variable. That leads to the messy "*odds = new int[*numOdds];"
 * syntax in the body and forces every call site to pass "&oddNums, &numOdds, ..." with
 * matching delete[] cleanup afterwards.
 *
 * Key notes:
 *   - Manual ownership: the caller is responsible for delete[]-ing both output arrays.
 *     Forget one and the program leaks memory.
 *   - Two layers of indirection: "int**" means "pointer to a pointer to int". Inside the
 *     function you write "*odds = new int[*numOdds];" - easy to miscount the *.
 *   - Every output parameter must be dereferenced before use - a single missed * is silently
 *     wrong code that compiles.
 *   - Sample 06 replaces the pointers with references; 07 switches to std::vector; 08 returns
 *     a struct by value. Each step cuts noise and bugs.
 */

#include <print>
#include <cstddef>

using namespace std;

void printIntArr(const int arr[], size_t size)
{
	for (size_t i{ 0 }; i < size; ++i) {
		print("{} ", arr[i]);
	}
	println("");
} 

void separateOddsAndEvens(const int arr[], size_t size, int** odds,
	size_t* numOdds, int** evens, size_t* numEvens)
{
	// Count the number of odds and evens
	*numOdds = *numEvens = 0;
	for (size_t i = 0; i < size; ++i) {
		if (arr[i] % 2 == 0) {
			++(*numEvens);
		} else {
			++(*numOdds);
		}
	}

	// Allocate two new arrays of the appropriate size.
	*odds = new int[*numOdds];
	*evens = new int[*numEvens];

	// Copy the odds and evens to the new arrays
	size_t oddsPos = 0, evensPos = 0;
	for (size_t i = 0 ; i < size; ++i) {
		if (arr[i] % 2 == 0) {
			(*evens)[evensPos++] = arr[i];
		} else {
			(*odds)[oddsPos++] = arr[i];
		}
	}
}

int main()
{
	int unSplit[]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -1, -2};
	int* oddNums{ nullptr };
	int* evenNums{ nullptr };
	size_t numOdds{ 0 }, numEvens{ 0 };

	separateOddsAndEvens(unSplit, std::size(unSplit), &oddNums, &numOdds, &evenNums, &numEvens);

	printIntArr(oddNums, numOdds);
	printIntArr(evenNums, numEvens);

	delete[] oddNums; oddNums = nullptr;
	delete[] evenNums; evenNums = nullptr;
}
