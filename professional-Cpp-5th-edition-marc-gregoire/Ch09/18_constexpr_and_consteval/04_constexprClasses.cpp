/*
 * Chapter 9 - constexpr Constructors and Member Functions
 *
 * Whole classes can participate in constant evaluation. Mark constructors and
 * member functions `constexpr` (or `consteval`), and instances can be built at
 * compile time and inspected from contexts that demand compile-time constants -
 * static_assert, template arguments, the size of a built-in array, and so on.
 *
 * Key notes:
 *   - `constexpr Matrix matrix{ 8, 2 };` runs the constructor at compile time;
 *     `matrix.getSize()` is then a compile-time constant usable as an array bound.
 *   - The defaulted default constructor here is implicitly `constexpr` because
 *     its body does nothing complex.
 *   - All member functions called during the constexpr evaluation must themselves
 *     be `constexpr`.
 *   - As of C++20, `constexpr` allows `std::vector`, `std::string`, virtual
 *     functions, and try/catch - the compile-time language is now almost as
 *     expressive as the runtime one.
 *   - You generally do NOT need `inline` on a `constexpr` function; constexpr
 *     implies the One Definition Rule relaxation already.
 */
#include <print>

using namespace std;

class Matrix
{
public:
	Matrix() = default; // Implicitly constexpr

	constexpr explicit Matrix(unsigned rows, unsigned columns)
		: m_rows{ rows }, m_columns{ columns }
	{
	}

	constexpr unsigned getSize() const
	{
		return m_rows * m_columns;
	}

private:
	unsigned m_rows{ 0 }, m_columns{ 0 };
};


int main()
{
	constexpr Matrix matrix{ 8, 2 };
	int linearizedMatrix[matrix.getSize()];
	println("Size of linearizedMatrix = {}", size(linearizedMatrix));

	constexpr Matrix matrixDefault;
}