/*
 * Chapter 2 - Format Strings and Argument Indices
 *
 * Each placeholder in a format string has the form {[index][:specifier]}. With an empty
 * pair of braces, std::format consumes arguments in the order they were passed. With an
 * explicit zero-based index ({0}, {1}, ...), it picks specific arguments by position -
 * the same argument can even be referenced multiple times. The two styles cannot be
 * mixed in one format string. Positional placeholders are the standard solution for
 * localization, where translated sentences often need a different word order.
 *
 * Key notes:
 *   - Automatic: format("{} of {}", a, b) - uses a then b in order.
 *   - Positional: format("{1} of {0}", a, b) - swaps them.
 *   - Mixing the two (e.g., "{0} {} {1}") is an error and fails the compile-time check.
 *   - To produce a literal { or } in the output, escape it: {{ or }}.
 *   - The third call here demonstrates a Chinese translation where the byte count and
 *     filename swap positions in the sentence, while the C++ argument list stays the same.
 *
 * Example:
 *     // Same C++ argument list, two different sentence orders:
 *     println("Read {0} bytes from {1}", n, "file1.txt");
 *     // The Chinese translation in main() reuses {1} then {0} - placeholder order
 *     // reversed, arguments to println() unchanged.
 */

#include <print>

using namespace std;

int main()
{
	int n{ 42 };

	println("Read {} bytes from {}", n, "file1.txt");
	println("Read {0} bytes from {1}", n, "file1.txt");
	println("从{1}中读取{0}个字节。", n, "file1.txt");
}
