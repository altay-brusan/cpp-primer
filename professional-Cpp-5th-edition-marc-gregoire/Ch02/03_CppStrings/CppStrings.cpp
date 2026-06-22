/*
 * Chapter 2 - The C++ std::string Class
 *
 * std::string (an instantiation of std::basic_string) is a first-class string type from
 * <string>. Operator overloading makes it feel like a built-in: + concatenates, += appends,
 * and the relational operators (==, !=, <, >, <=, >=, <=>) compare the actual characters,
 * not pointer values like C strings would. Memory is managed automatically - allocation,
 * resizing, copying, and destruction all happen for you when the string goes out of scope.
 * compare() exists for strcmp-style three-way comparison, but for clearer code use C++20's
 * <=> with is_lt / is_gt / is_eq. Useful methods include find(), rfind(), substr(),
 * replace(), starts_with / ends_with (C++20), and contains() (C++23).
 *
 * Key notes:
 *   - compare() returns int (negative / zero / positive), NOT bool. Writing
 *     `if (a.compare(b)) { ... "equal" }` is a classic bug because non-zero means NOT equal.
 *     For equality, simply use `a == b`.
 *   - find() returns std::string::npos (a sentinel size_t) when the substring is not
 *     present - always test against npos before using the returned index.
 *   - "Hello"s requires `using namespace std::string_literals;` (or std::literals, or std).
 *     `auto x { "Hi"s };` deduces std::string; `auto y { "Hi" };` deduces const char*.
 *   - `auto& z { "Hi" };` binds to const char[3] - the underlying array, not a pointer.
 *   - CTAD pitfall: `vector names { "John", "Sam" };` deduces vector<const char*>, not
 *     vector<string>. Add the s suffix: `vector names { "John"s, "Sam"s };`.
 *   - Since C++20, std::string is constexpr and can be used in compile-time computations.
 *   - c_str() returns a const char* for C-interop; the pointer is invalidated by any
 *     reallocation or by destruction of the string.
 *
 * Example:
 *     auto result { a <=> b };
 *     if (is_lt(result)) { ... }   // a < b
 *     if (is_eq(result)) { ... }   // a == b
 *     if (is_gt(result)) { ... }   // a > b
 */

#include <print>
#include <string>
#include <compare>

using namespace std;

int main()
{
	{
		string a{ "12" };
		string b{ "34" };
		string c{ a + b };    // c is "1234"
		println("{}", c);

		a += b;    // a is "1234"
		println("{}", a);
	}

	println("");

	{
		string a{ "Hello" };
		string b{ "World" };
		println("'{}' < '{}' = {}", a, b, a < b);
		println("'{}' > '{}' = {}", a, b, a > b);
	}

	println("");

	{
		string a{ "12" };
		string b{ "34" };

		auto result{ a.compare(b) };  // strcmp-like: <0, 0, or >0 - easy to misuse
		if (result < 0) { println("less"); }
		if (result > 0) { println("greater"); }
		if (result == 0) { println("equal"); }
	}

	println("");

	{
		// C++20 three-way comparison operator
		string a{ "12" };
		string b{ "34" };
		auto result{ a <=> b };
		if (is_gt(result)) { println("greater"); }
		if (is_lt(result)) { println("less"); }
		if (is_eq(result)) { println("equal"); }
	}

	println("");

	{
		string myString{ "hello" };

		myString += ", there";

		string myOtherString{ myString };

		if (myString == myOtherString) {
			myOtherString[0] = 'H';
		}

		println("{}", myString);
		println("{}", myOtherString);
	}

	println("");

	{
		string strHello{ "Hello!!" };
		string strWorld{ "The World..." };
		auto position{ strHello.find("!!") };
		if (position != string::npos) {
			// Found the "!!" substring, now replace it.
			strHello.replace(position, 2, strWorld.substr(3, 6));
		}
		println("{}", strHello);

		// Test contains().
		string toFind{ "World" };
		println("{}", strWorld.contains(toFind));  // true
		println("{}", strWorld.contains('.'));     // true
		println("{}", strWorld.contains("Hello")); // false
	}
	
	println("");

	{
		auto string1{ "Hello World" };    // string1 is a const char*.
		auto& string2{ "Hello World" };   // string2 is a const char[12].
		auto string3{ "Hello World"s };   // string3 is an std::string (user-defined literal s).
	}
}
