/*
 * Chapter 12 - Variable Templates (C++14)
 *
 * Most templates make functions or classes. Variable templates make
 * *constants* parameterized on a type. The canonical example is `pi`:
 * the same conceptual constant exists as `float`, `double`, and
 * `long double`, each with the precision the chosen type can hold.
 *
 *     pi<float>        - 3.14159274f (rounded to float precision)
 *     pi<long double>  - up to ~19 digits depending on platform
 *
 * Key notes:
 *   - The Standard Library defines `std::numbers::pi_v<T>` in `<numbers>`
 *     using exactly this mechanism. The custom version here is for
 *     pedagogy; reach for the standard one in real code.
 *   - `constexpr` makes each instantiation usable at compile time.
 *   - Variable templates can also be specialized, just like class
 *     templates.
 *   - Common uses: `std::is_same_v`, `std::is_integral_v`, etc. - all the
 *     `_v` trait helpers in `<type_traits>` are variable templates.
 */
template <typename T>
constexpr T pi{ T{ 3.141592653589793238462643383279502884 } };

int main()
{
	float piFloat{ pi<float> };
	auto piLongDouble{ pi<long double> };
}
