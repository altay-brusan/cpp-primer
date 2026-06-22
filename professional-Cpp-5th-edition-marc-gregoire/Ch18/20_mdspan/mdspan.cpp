/*
 * Chapter 18 - std::mdspan
 *
 * std::mdspan (C++23) is a non-owning multidimensional view over a flat,
 * contiguous block of memory. The same vector of 8 ints is viewed as a 2x4
 * matrix three ways: the default row-major (layout_right) layout, column-major
 * (layout_left), and with one extent fixed and the other a dynamic_extent.
 * Elements are addressed with the multi-argument subscript mdSpan[i, j].
 *
 * Key notes:
 *   - Requires a C++23 toolchain with <mdspan> support.
 */

#include <print>
#include <vector>
#include <mdspan>

using namespace std;

template <typename T>
void print2Dmdspan(const T& mdSpan)
{
	for (size_t i{ 0 }; i < mdSpan.extents().extent(0); ++i) {
		for (size_t j{ 0 }; j < mdSpan.extents().extent(1); ++j) {
			print("{} ", mdSpan[i, j]);
		}
		println("");
	}
}

int main()
{
	vector data{ 1, 2, 3, 4, 5, 6, 7, 8 };

	{
		// View data as a 2D array of 2 rows with 4 integers each,
		// using the default row-major layout policy.
		mdspan data2D{ data.data(), 2, 4 };
		print2Dmdspan(data2D);
	}

	println("");

	{
		// View data as a 2D array of 2 rows with 4 integers each,
		// using the column-major layout policy.
		mdspan<int, extents<int, 2, 4>, layout_left> data2D{ data.data() };
		print2Dmdspan(data2D);
	}

	println("");

	{
		// View data as a 2D array of 2 rows with 4 integers each,
		// using the default row-major layout policy.
		mdspan<int, extents<int, 2, dynamic_extent>> data2D{ data.data(), 4 };
		print2Dmdspan(data2D);
	}
}
