/*
 * Chapter 2 - The std::string_view Class
 *
 * std::string_view (from <string_view>, since C++17) is a non-owning, read-only view of a
 * character sequence - effectively a <pointer, length> pair with most of std::string's
 * read-only interface. It is cheap to copy, so pass it by value rather than by reference.
 * Use string_view as the parameter type for any function that needs a read-only string:
 * a single overload then accepts std::string, const char*, string literals, char arrays,
 * and substrings, all without copying a single byte.
 *
 * Key notes:
 *   - string_view does NOT own the characters it points to - the underlying buffer must
 *     outlive the view. Never bind a string_view to a temporary std::string:
 *         string_view sv { s + " World!" };  // UB: temporary destroyed at semicolon.
 *   - No implicit conversion FROM string_view TO std::string. Use an explicit constructor
 *     or .data():
 *         handleExtension(string { extractExtension("file.ext") });
 *         handleExtension(extractExtension("file.ext").data());
 *   - You cannot do `string + string_view`. Workarounds: `str + string{sv}`, or
 *     `str.append(sv.data(), sv.size())`.
 *   - Has data() but NOT c_str() - the viewed range is not guaranteed to be NUL terminated.
 *   - Extra methods compared to std::string: remove_prefix(n), remove_suffix(n) - they
 *     just slide the start/end pointers, no copying.
 *   - Constructor `string_view{ rawPtr, length }` accepts buffers that are not NUL
 *     terminated, or skips the strlen scan when you already know the length.
 *   - Prefer returning std::string (not string_view) from functions that produce new
 *     content, to avoid handing back a dangling view if the source reallocates.
 *   - Storing string_view (or const string&) as a class data member is risky for the same
 *     reason; store a std::string when you need to own the data.
 *   - "Hi"sv is a string_view literal (compile-time length); requires `using namespace
 *     std::string_view_literals;` (or std::literals, or std).
 *
 * Example:
 *     string_view extractExtension(string_view filename) {
 *         return filename.substr(filename.rfind('.'));
 *     }
 */

#include <print>
#include <string>
#include <string_view>
#include <cstddef>

using namespace std;

string extractExtension(string_view filename)
{
	// Return a copy of the extension.
	return string{ filename.substr(filename.rfind('.')) };
}

int main()
{
	{
		// C++ std::string.
		string filename{ R"(c:\temp\my file.ext)" };
		println("C++ string: {}", extractExtension(filename));

		// C-style string.
		const char* cString{ R"(c:\temp\my file.ext)" };
		println("C string: {}", extractExtension(cString));

		// String literal.
		println("Literal: {}", extractExtension(R"(c:\temp\my file.ext)"));

		// Raw string buffer with given length.
		const char* raw{ "test.ext" };
		size_t length{ 8 };
		println("Raw: {}", extractExtension({ raw, length }));
		println("Raw: {}", extractExtension(string_view{ raw, length }));
	}

	{
		// Concatenation with string_view.
		string str{ "Hello" };
		string_view sv{ " world" };
		//auto result{ str + sv };  // Error, does not compile!
		auto result1{ str + string { sv } };

		string result2{ str };
		result2.append(sv.data(), sv.size());
		
		println("{}\n{}", result1, result2);
	}

	{
		// Using the standard user-defined literal sv.
		auto sv{ "My string_view"sv };
	}
}
