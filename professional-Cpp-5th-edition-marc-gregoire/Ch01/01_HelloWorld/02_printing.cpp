/*
 * Chapter 1 - I/O Streams (modernized with std::println from C++23)
 *
 * std::println() from <print> is the modern one-shot way to format and emit a line. It writes
 * to std::cout by default and appends a newline. Placeholders {} are filled left-to-right with
 * the trailing arguments. To target a different stream (for example std::cerr, the error
 * console), pass the stream object as the first argument.
 *
 * Key notes:
 *   - std::println(fmt, args...) is roughly std::print + a trailing newline (no manual '\n').
 *   - Argument order is positional; reorder with indices like "{1} {0}" if needed.
 *   - For just formatting without printing, std::format() from <format> returns a std::string.
 *   - printf()/scanf() still compile but offer no type safety; prefer std::format/println.
 *
 * Example:
 *     std::println(std::cerr, "Error: {}", code);   // route output to stderr
 */

#include <print>
#include <iostream>

int main()
{
	std::println("Hello, World!");
	
	std::println("There are {} ways I love you.", 219);
	
	std::println("{} + {} = {}", 2, 4, 6);
	
	std::println(std::cerr, "Error: {}", 6);

	return 0;
}
