/*
 * Chapter 10 - C++ Casts (1/4): static_cast
 *
 * `static_cast<T>(...)` is the everyday cast. It performs conversions the
 * compiler can reason about at compile time: numeric conversions, upcasts,
 * and *unchecked* downcasts in an inheritance hierarchy.
 *
 * Three uses shown here:
 *   - `static_cast<double>(i) / j`             - integer-to-double promotion to force float division.
 *   - `b = d;`                                 - implicit upcast (no cast needed).
 *   - `d = static_cast<Derived*>(b);`          - downcast; YOU promise b actually
 *                                                points to a Derived. No runtime check.
 *   - `Derived& dr{ static_cast<Derived&>(br) };` - reference downcast.
 *
 * Key notes:
 *   - For polymorphic downcasts you can't be sure of, use `dynamic_cast`
 *     (04_dynamic_cast.cpp). That one *does* check at runtime.
 *   - static_cast WILL NOT compile for unrelated types - use `reinterpret_cast`
 *     for that (and even then, only when you know what you're doing).
 *   - For numeric conversions on modern C++, also consider `std::bit_cast`
 *     and `std::to_underlying` for crisper intent. See 03_bit_cast.cpp.
 */
class Base
{
public:
	virtual ~Base() = default;
};

class Derived : public Base
{
public:
	virtual ~Derived() = default;
};

int main()
{
	int i{ 3 };
	int j{ 4 };
	double result{ static_cast<double>(i) / j };   // forces double division -> 0.75


	Base* b{ nullptr };
	Derived* d{ new Derived{} };

	b = d;                                 // upcast - no cast needed
	d = static_cast<Derived*>(b);          // downcast - your responsibility to be right

	Base base;
	Derived derived;

	Base& br{ derived };
	Derived& dr{ static_cast<Derived&>(br) };

	delete b;   // clean up the heap-allocated Derived
}
