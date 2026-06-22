/*
 * Chapter 2 - Low-Level Numeric Conversions: to_chars / from_chars
 *
 * <charconv> exposes std::to_chars() and std::from_chars(): a pair of locale-independent,
 * allocation-free, exception-free conversion functions tuned for performance. The caller
 * supplies the raw character buffer [first, last); to_chars() writes the textual form of
 * a number into it, and from_chars() parses one back out. Both return a small struct -
 * to_chars_result or from_chars_result - with a pointer indicating where they stopped
 * and a std::errc error code. They are designed for "perfect round-tripping" of
 * floating-point values: serialize then parse, and you get back the exact same bits.
 *
 * Key notes:
 *   - Signatures look like:
 *       to_chars_result   to_chars(char* first, char* last, T value, ...);
 *       from_chars_result from_chars(const char* first, const char* last, T& value, ...);
 *   - to_chars_result { char* ptr; std::errc ec; }
 *     ec == errc{} means success; ec == errc::value_too_large means the buffer was too
 *     small (ptr == last in that case).
 *   - from_chars_result { const char* ptr; std::errc ec; }
 *     ec == errc::invalid_argument: nothing parsed (ptr == first).
 *     ec == errc::result_out_of_range: value too large for the target type.
 *   - from_chars() does NOT skip leading whitespace - unlike stoi(). Pre-trim if needed.
 *   - to_chars() for floats supports std::chars_format::scientific / fixed / hex / general
 *     and an optional precision; default produces the shortest round-trip representation.
 *   - These functions are ideal for JSON/XML and other text wire formats where speed,
 *     determinism, and exact round-trip matter.
 *   - Structured bindings (C++17) make the result types ergonomic:
 *         auto [ptr, ec] { to_chars(buf, buf + n, value) };
 *
 * Example:
 *     std::string out(50, ' ');
 *     auto [ptr, ec] { std::to_chars(out.data(), out.data() + out.size(), 12345) };
 *     if (ec == std::errc{}) { ... use the written range [out.data(), ptr) ... }
 */

#include <print>
#include <string>
#include <cstddef>
#include <charconv>

using namespace std;

int main()
{
	const size_t BufferSize{ 50 };

	{
		// to_chars() without structured binding.
		string out(BufferSize, ' '); // A string of BufferSize space characters.
		auto result{ to_chars(out.data(), out.data() + out.size(), 12345) };
		if (result.ec == errc{}) { println("{}", out); /* Conversion successful. */ }
	}

	{
		// to_chars() with structured binding.
		string out(BufferSize, ' '); // A string of BufferSize space characters.
		auto [ptr, error] { to_chars(out.data(), out.data() + out.size(), 12345) };
		if (error == errc{}) { println("{}", out); /* Conversion successful. */ }
	}

	{
		// Demonstrating perfect round-tripping.
		double value1{ 0.314 };
		string out(BufferSize, ' '); // A string of BufferSize space characters.
		auto [ptr1, error1] { to_chars(out.data(), out.data() + out.size(), value1) };
		if (error1 == errc{}) { println("{}", out); /* Conversion successful. */ }

		double value2;
		auto [ptr2, error2] { from_chars(out.data(), out.data() + out.size(), value2) };
		if (error2 == errc{}) {
			if (value1 == value2) {
				println("Perfect roundtrip");
			} else {
				println("No perfect roundtrip?!?");
			}
		}
	}
}
