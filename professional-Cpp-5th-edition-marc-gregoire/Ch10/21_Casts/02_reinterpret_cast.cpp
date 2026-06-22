/*
 * Chapter 10 - C++ Casts (2/4): reinterpret_cast
 *
 * `reinterpret_cast<T>(...)` is the "I know what I'm doing, treat these bits
 * as a T" cast. It performs no conversion - just changes the type that the
 * compiler thinks the value has.
 *
 * Use cases:
 *   - Casting between unrelated pointer types (no inheritance relation).
 *   - Casting a reference to an unrelated reference type.
 *   - Casting integers to/from pointers (rare, low-level interop).
 *
 * Key notes:
 *   - This is the cast you should reach for *least*. If a `static_cast` works,
 *     use it. If you find yourself using reinterpret_cast routinely, your
 *     design probably needs revisiting.
 *   - Going through `void*` only needs `static_cast` (in one direction it's
 *     even implicit).
 *   - The "treat as a different type" semantics depend on a long list of
 *     standard rules (strict aliasing, object lifetime, alignment) that are
 *     easy to violate. For bit-pattern conversions of trivially copyable
 *     types, prefer `std::bit_cast` (03_bit_cast.cpp).
 */
class X {};
class Y {};

int main()
{
	X x;
	Y y;

	X* xp{ &x };
	Y* yp{ &y };

	// Pointer conversion between unrelated classes - static_cast doesn't work.
	xp = reinterpret_cast<X*>(yp);

	// No cast required for conversion from pointer to void*.
	void* p{ xp };
	// static_cast is enough for the reverse direction from void*.
	xp = static_cast<X*>(p);

	// Reference conversion between unrelated classes - reinterpret_cast needed.
	X& xr{ x };
	Y& yr{ reinterpret_cast<Y&>(x) };
}
