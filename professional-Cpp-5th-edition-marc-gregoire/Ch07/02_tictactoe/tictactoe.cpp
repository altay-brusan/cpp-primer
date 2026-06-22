/*
 * Chapter 7 - Multidimensional Stack Arrays
 *
 * A two-dimensional stack array such as `char board[3][3]` is laid out as a single
 * contiguous block of 3 * 3 = 9 bytes. The compiler hides the address arithmetic behind
 * the `[x][y]` syntax, but the underlying memory is still a flat sequence. Because the
 * dimensions must be compile-time constants, this style is fine for fixed-size boards but
 * cannot be sized at run time. The braces `{}` zero-initialize every element.
 *
 * Key notes:
 *   - Stack-based multidimensional arrays are contiguous in memory - good for cache locality.
 *   - Choice of which subscript is x vs y is arbitrary; pick one convention and stick to it.
 *   - For run-time sizes, use `std::vector<std::vector<char>>` or a hand-rolled 1-D buffer
 *     indexed as `x * yDim + y` rather than the `char**` pattern shown in 03_CharacterBoard.
 */

int main()
{
	char board[3][3]{};       // 3x3 stack-allocated, zero-initialized: all cells are '\0'
	// Test code
	board[0][0] = 'X';   // X puts marker in position (0,0).
	board[2][1] = 'O';   // O puts marker in position (2,1).
}
