/*
 * Chapter 9 - consteval (Immediate Functions)
 *
 * A `consteval` function - introduced in C++20 - MUST be evaluated at compile time.
 * The compiler refuses any call whose arguments are not themselves compile-time
 * constants. There is no runtime fallback the way there is with `constexpr`.
 *
 * Key notes:
 *   - `constexpr double const_inch{ 6.0 };` is a compile-time constant, so
 *     `inchToMm(const_inch)` is fine.
 *   - `double dynamic_inch{ 8.0 };` is a runtime value; the commented-out
 *     `inchToMm(dynamic_inch)` would be a compile error.
 *   - Use `consteval` when the function only makes sense at compile time -
 *     literal-encoder helpers, parsing format strings, generating compile-time
 *     tables.
 *   - Cannot take the address of a `consteval` function - there is no runtime
 *     instance to point at.
 */
//constexpr double inchToMm(double inch) { return inch * 25.4; }
consteval double inchToMm(double inch) { return inch * 25.4; }

int main()
{
	constexpr double const_inch{ 6.0 };
	constexpr double mm1{ inchToMm(const_inch) };    // at compile time

	double dynamic_inch{ 8.0 };
	//double mm2{ inchToMm(dynamic_inch) };  // compile-time error
}
