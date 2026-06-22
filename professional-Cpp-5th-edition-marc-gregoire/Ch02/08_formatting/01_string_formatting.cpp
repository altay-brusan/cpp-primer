/*
 * Chapter 2 - String Formatting (printf vs. streams vs. std::format)
 *
 * C++ offers three families of text output. printf()-style C functions accept a format
 * string with %d / %s / ... specifiers but are NOT type safe and cannot be extended to
 * user-defined types - mismatched specifiers are undefined behavior. C++ I/O streams
 * (cout <<) are type safe and user-extensible but inline the values inside the message,
 * which makes localization awkward. C++20's std::format() (from <format>) combines the
 * best of both: a separate, readable format string with {} placeholders, full type
 * safety, locale awareness, and extensibility via std::formatter specializations. C++23
 * adds std::print() and std::println() as the print equivalents - and they handle
 * Unicode output reliably, unlike cout on many terminals.
 *
 * Key notes:
 *   - `printf("%d", x)` with the wrong type is silently broken; `format("{}", x)` is a
 *     compile error if x has no formatter.
 *   - `format()` returns a std::string. `print()` writes to a stream. `println()` adds a
 *     newline and flushes nothing extra. All three take the same format strings.
 *   - {} is the placeholder. Use {{ and }} to emit literal braces.
 *   - `println("...");` defaults to stdout; pass a stream as the first argument to redirect.
 *   - print()/println() default to UTF-8 and tend to render non-ASCII (e.g., emoji,
 *     Japanese) correctly where `cout` would garble it.
 *
 * Example:
 *     std::println("x = {}, y = {}", x, y);            // type safe, extensible, Unicode-aware
 *     auto s { std::format("x = {}, y = {}", x, y) };  // capture the formatted std::string
 */

#include <print>
#include <format>
#include <iostream>

using namespace std;

int main()
{
	int x{ 42 };
	int y{ 84 };

	// C-style function.
	printf("x has value %d and y has value %d.\n", x, y);

	// C++ I/O stream.
	cout << "x has value " << x << " and y has value " << y << '.' << endl;

	// C++20 std::format() + I/O streams.
	cout << format("x has value {} and y has value {}.", x, y) << endl;

	// C++23 std::println().
	println("x has value {} and y has value {}.", x, y);

	// C++23 std::println() + Unicode.
	println("こんにちは世界");
	
	// I/O streams + Unicode.
	cout << "こんにちは世界" << endl;

	// C++23 std::println() + Unicode emojis.
	println("😀");
}
