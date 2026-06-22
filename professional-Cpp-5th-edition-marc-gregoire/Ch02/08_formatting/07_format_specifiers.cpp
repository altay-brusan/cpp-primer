/*
 * Chapter 2 - Format Specifiers (full grammar)
 *
 * The full specifier grammar follows the colon inside a placeholder:
 *     [[fill]align][sign][#][0][width][.precision][L][type]
 * Every part is optional and order matters. The examples below walk through each piece
 * in isolation; combining them gives fine-grained control over width, alignment, padding,
 * sign display, numeric base, precision, and locale awareness.
 *
 * Key notes:
 *   - width: minimum field width. Either a literal integer ({:5}) or a nested {} that
 *     pulls the width from another argument - either next-in-line ({:{}}) or by index
 *     ({1:{0}}, where {0} is the width and {1} is the value).
 *   - [fill]align: optional fill character followed by alignment:
 *         <  left  (default for non-numeric)
 *         >  right (default for numeric)
 *         ^  center
 *     Without an explicit width, [fill]align has nothing to fill and is ignored.
 *   - sign: '-' (default, negatives only), '+' (always show sign), ' ' (space for
 *     positives, '-' for negatives).
 *   - #: alternate form. Adds 0b / 0B / 0x / 0X / 0 prefix to binary, hex, and octal
 *     integers; forces a decimal point on floating-point output.
 *   - 0: zero-pad numerics to width. Inserted AFTER any sign and after a 0b/0x/0 prefix.
 *     Ignored if an alignment was specified.
 *   - precision (.N): for floats it is digits after the decimal point; for strings it is
 *     the maximum number of characters to output. Can also be dynamic via nested {}.
 *   - type letters:
 *         integers       b / B (binary), d (decimal), o (octal), x / X (hex)
 *         floating-point e / E (sci), f / F (fixed), g / G (general), a / A (hex)
 *         characters     c (literal char), or any int form for the code value
 *         strings        s
 *         booleans       s (true/false), or any int form for 1/0
 *         pointers       p (0x... hex)
 *   - L: locale-aware numeric formatting. Combined with a locale (e.g., std::locale{"nl"}),
 *     it inserts the locale's decimal separator and grouping characters - the final cout
 *     line prints 1,2 instead of 1.2 under a Dutch locale.
 *
 * Example:
 *     int i { 42 };
 *     println("|{:#06X}|", i);   // |0X002A|  (alternate hex, zero-pad to width 6)
 *     println("|{:_^7}|", i);    // |__42___| (center align with '_' fill)
 *     println("|{2:{0}.{1}f}|", 12, 3, 3.1415 / 2.3);  // dynamic width and precision
 */

#include <print>
#include <string>
#include <iostream>

using namespace std;

int main()
{
	{
		// width
		int i{ 42 };
		println("|{:5}|", i);       // |   42|
		println("|{:{}}|", i, 7);   // |     42|
		println("|{1:{0}}|", 7, i); // |     42|
	}

	println("");

	{
		// [fill]align
		int i{ 42 };
		println("|{:7}|", i);     // |     42|
		println("|{:<7}|", i);    // |42     |
		println("|{:_>7}|", i);   // |_____42|
		println("|{:_^7}|", i);   // |__42___|

		println("|{:=>16}|", "");  // |================|
	}

	println("");

	{
		// sign
		int i{ 42 };
		println("|{:<5}|", i);   // |42   |
		println("|{:<+5}|", i);  // |+42  |
		println("|{:< 5}|", i);  // | 42  |
		println("|{:< 5}|", -i); // |-42  |
	}

	println("");

	{
		// Integral types
		int i{ 42 };
		println("|{:10d}|", i);   // |        42|
		println("|{:10b}|", i);   // |    101010|
		println("|{:#10b}|", i);  // |  0b101010|
		println("|{:10X}|", i);   // |        2A|
		println("|{:#10X}|", i);  // |      0X2A|
	}

	println("");

	{
		// String types
		string s{ "ProCpp" };
		println("|{:_^10}|", s); // |__ProCpp__|
	}

	println("");

	{
		// Floating-point types
		double d{ 3.1415 / 2.3 };
		println("|{:12g}|", d);                         // |     1.36587|
		println("|{:12.2}|", d);                        // |         1.4|
		println("|{:12e}|", d);                         // |1.365870e+00|

		int width{ 12 };
		int precision{ 3 };
		println("|{2:{0}.{1}f}|", width, precision, d); // |       1.366|
		println("|{2:{0}.{1}}|", width, precision, d);  // |        1.37|
	}

	println("");

	{
		// 0
		int i{ 42 };
		println("|{:06d}|", i);   // |000042|
		println("|{:+06d}|", i);  // |+00042|
		println("|{:06X}|", i);   // |00002A|
		println("|{:#06X}|", i);  // |0X002A|
	}

	println("");

	{
		float f{ 1.2f };
		cout << format(std::locale{ "nl" }, "|{:Lg}|\n", f);  // |1,2|
	}

	println("");
}
