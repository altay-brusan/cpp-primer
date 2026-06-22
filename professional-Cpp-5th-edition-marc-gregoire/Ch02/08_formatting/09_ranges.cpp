/*
 * Chapter 2 - Formatting Ranges, Pairs, and Tuples (C++23)
 *
 * Standard containers, std::pair, and std::tuple have built-in formatters in C++23. By
 * default a range prints as [a, b, c], a pair or tuple as (a, b), and string/char
 * elements appear in their escaped debug form (with quotes and visible \t, \n, etc.).
 * The specifier after the FIRST colon styles the whole composite value; introducing a
 * SECOND colon hands a specifier down to each element. Nested composites can have a
 * specifier per level, so a `vector<vector<int>>` can be controlled all the way down.
 *
 * Key notes:
 *   - Default forms:
 *         vector<int>{11,22,33} -> [11, 22, 33]
 *         pair{11, 22}          -> (11, 22)
 *         vector<string>{"a"}   -> ["a"]   (string elements quoted/escaped)
 *   - Outer spec ({:...}) styles the WHOLE range. Example: {:*^16} centers the bracketed
 *     list inside a width-16 field.
 *   - Element spec ({::...}, note the second colon) is forwarded to each element's
 *     formatter. Example: {::*^6} pads each int in a vector to width 6 with '*'.
 *   - The 'n' flag drops the surrounding brackets: {:n} -> 11, 22, 33 (no [ ]).
 *   - The 's' / '?s' flags on a range of chars treat it as a string (with or without
 *     debug escaping).
 *   - The 'm' flag on a pair switches the separator from ", " to ": " - useful for
 *     map-like printing.
 *   - Nesting: {:n:n:*^4} on a vector<vector<int>> means "no outer brackets, no inner
 *     brackets, each int centered in a width-4 '*'-padded field".
 *
 * Example:
 *     std::vector vv { std::vector{11, 22}, std::vector{33, 44, 55} };
 *     std::println("{:n:n:*^4}", vv);   // *11*, *22*, *33*, *44*, *55*
 */

#include <print>
#include <vector>
#include <string>

using namespace std;

int main()
{
	vector values{ 11, 22, 33 };
	println("{}", values);         // [11, 22, 33]
	println("{:n}", values);       // 11, 22, 33

	println("{{{:n}}}", values);   // {11, 22, 33}

	println("{:*^16}", values);    // **[11, 22, 33]**
	println("{:*^16n}", values);   // ***11, 22, 33***

	println("{::*^6}", values);    // [**11**, **22**, **33**]

	println("{:n:*^6}", values);   // **11**, **22**, **33**

	vector strings{ "Hello"s, "World!\t2023"s };
	println("{}", strings);        // ["Hello", "World!\t2023"]
	println("{:}", strings);       // ["Hello", "World!\t2023"]
	println("{::}", strings);      // [Hello, World!    2023]
	println("{:n:}", strings);     // Hello, World!    2023

	vector chars{ 'W', 'o', 'r', 'l', 'd', '\t', '!' };
	println("{}", chars);          // ['W', 'o', 'r', 'l', 'd', '\t', '!']
	println("{::#x}", chars);      // [0x57, 0x6f, 0x72, 0x6c, 0x64, 0x9, 0x21]
	println("{:s}", chars);        // World    !
	println("{:?s}", chars);       // "World\t!"

	pair p{ 11, 22 };
	println("{}", p);              // (11, 22)
	println("{:n}", p);            // 11, 22
	println("{:m}", p);            // 11: 22

	vector<vector<int>> vv{ {11, 22}, {33, 44, 55} };
	println("{}", vv);             // [[11, 22], [33, 44, 55]]
	println("{:n}", vv);           // [11, 22], [33, 44, 55]
	println("{:n:n}", vv);         // 11, 22, 33, 44, 55
	println("{:n:n:*^4}", vv);     // *11*, *22*, *33*, *44*, *55*
}
