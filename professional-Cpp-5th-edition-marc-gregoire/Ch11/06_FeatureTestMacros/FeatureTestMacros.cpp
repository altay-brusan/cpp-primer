/*
 * Chapter 11 - Feature-Test Macros
 *
 * Every standardized C++ language and library feature comes with a
 * documented macro you can `#ifdef` on. They are the standard way to write
 * code that works across compilers and standard versions without resorting
 * to compiler-specific tricks.
 *
 * Examples (see https://en.cppreference.com/w/cpp/feature_test):
 *   - __cpp_lib_format     - <format> header support level.
 *   - __cpp_concepts       - the C++20 concepts feature.
 *   - __cpp_modules        - module support.
 *   - __cpp_range_based_for - range-based for loops (very old at this point).
 *
 * Each macro expands to an integer that increases when the feature gets
 * revised, so `#if __cpp_xxx >= 201907L` is more precise than a bare
 * `#ifdef`.
 *
 * Key notes:
 *   - Use feature-test macros INSIDE the source file, not in CMake or build
 *     glue. They reflect what *this* compile actually sees.
 *   - Avoid `__cplusplus >= 202002L` as a substitute - some compilers lag
 *     individual features even when they bump the cplusplus value.
 */
#include <print>

using namespace std;

int main()
{
#ifdef __cpp_range_based_for
	println("Range-based for loops are supported!");
#else
	println("Bummer! Range-based for loops are NOT supported!");
#endif
}
