/*
 * Chapter 2 - Runtime Format Strings (vformat / vprint_unicode)
 *
 * std::format() and std::println() require a compile-time format string, which is great
 * for safety but unworkable when the format string itself must be chosen at run time -
 * the canonical case being localization, where the right phrase is loaded from a resource
 * file based on the current language. The escape hatch is the "v" family: std::vformat(),
 * std::vprint_unicode(), and std::vprint_nonunicode(). They take a runtime format string
 * plus a type-erased argument pack produced by std::make_format_args(), so argument
 * handling stays type-safe even though the format string is opaque to the compiler.
 *
 * Key notes:
 *   - std::vformat(fmt, std::make_format_args(args...)) returns a std::string.
 *   - std::vprint_unicode(stream, fmt, std::make_format_args(args...)) writes to a stream.
 *   - Use the v* form whenever the format string is not a literal/constexpr - e.g.,
 *     loaded from a .po/.json/.xml localization resource.
 *   - Errors in the format string can no longer be caught at compile time; an invalid
 *     spec at run time throws std::format_error (see 06_exceptions.cpp).
 *   - Plain `print(fmt, ...)` will not compile when fmt is a runtime value - the
 *     commented-out line at the bottom demonstrates this.
 *
 * Example:
 *     auto fmt { GetLocalizedFormat(currentLanguage) };  // runtime-chosen string_view
 *     std::vprint_unicode(std::cout, fmt, std::make_format_args(a, b));
 */

#include <print>
#include <format>
#include <string_view>
#include <iostream>

using namespace std;

enum class Language { English, Dutch };

string_view GetLocalizedFormat(Language language)
{
	switch (language) {
	case Language::English:
		return "Numbers: {0} and {1}.";
	case Language::Dutch:
		return "Getallen: {0} en {1}.";
	}
}

int main()
{
	Language language{ Language::English };
	int number1 = 1;
	int number2 = 2;
	vprint_unicode(cout, GetLocalizedFormat(language), make_format_args(number1, number2));
	println("");
	language = Language::Dutch;
	vprint_unicode(cout, GetLocalizedFormat(language), make_format_args(number1, number2));

	// The following call using print() does not compile.
	//print(GetLocalizedFormat(language), 1, 2);
}