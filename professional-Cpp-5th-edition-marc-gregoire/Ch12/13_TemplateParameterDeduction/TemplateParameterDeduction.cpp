/*
 * Chapter 12 - Template Parameter Deduction Order
 *
 * For function templates, the compiler can deduce a trailing parameter if
 * it's used in the function's arguments. But it can't deduce a parameter
 * that only appears in the return type - you have to spell that one out
 * explicitly (or give it a default).
 *
 * `addA<RetType, T1, T2>`:
 *   - T1, T2 are deduced from the call.
 *   - RetType is in the return type ONLY. Must be passed explicitly.
 *   - `addA<long long, int, int>(1, 2)` - all three explicit.
 *   - `addA<long long>(1, 2)`        - explicit RetType, deduce T1, T2.
 *   - `addA(1, 2)`                   - won't compile, RetType unknown.
 *
 * `addB`:
 *   - RetType has a default of `long long`. Now the bare call works:
 *     `addB(1, 2)` returns a long long.
 *
 * Key notes:
 *   - Order matters: explicit template arguments are matched left-to-right
 *     against the parameter list. Place parameters that must be explicit
 *     FIRST so they don't block deduction of the later ones.
 *   - If a parameter that only appears in the return type has no default
 *     and isn't supplied explicitly, the call doesn't compile.
 */
template<typename RetType, typename T1, typename T2>
RetType addA(const T1& t1, const T2& t2) { return t1 + t2; }

template <typename RetType = long long, typename T1, typename T2>
RetType addB(const T1& t1, const T2& t2) { return t1 + t2; }

int main()
{
	auto result1{ addA<long long, int, int>(1, 2) };
	auto result2{ addA<long long>(1, 2) };

	auto result{ addB(1, 2) };
}
