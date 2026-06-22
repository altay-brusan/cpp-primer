/*
 * Chapter 2 - Compile-Time Format String Checks
 *
 * The first argument to std::format(), std::print(), and std::println() must be a
 * compile-time constant. The library validates placeholder count and types against the
 * argument list at compile time, so a malformed spec or wrong argument is a build error,
 * not a run-time surprise. A plain std::string (or string_view) variable cannot be used
 * directly because its value is only known at run time; a constexpr literal or a
 * constexpr auto variable works because the compiler can inspect the contents.
 *
 * Key notes:
 *   - `println(s);` where s is a std::string does NOT compile - intentionally.
 *   - `println("{}", s);` is the correct way to print the value of s.
 *   - `constexpr auto fmt { "Value: {}" }; println(fmt, 11);` compiles - the compiler still
 *     sees the literal.
 *   - When the format string truly must be chosen at run time (e.g., loaded from a
 *     localization file), bypass the compile-time check with std::vformat /
 *     std::vprint_unicode plus std::make_format_args - see 05_localization.cpp.
 */

#include <print>
#include <string>

using namespace std;


int main()
{
	{
		string s{ "Hello World!" };
		//println(s);   // Error! Does not compile.
		println("{}", s);
	}

	{
		constexpr auto formatString{ "Value: {}" };
		println(formatString, 11);  // Value: 11
	}
}