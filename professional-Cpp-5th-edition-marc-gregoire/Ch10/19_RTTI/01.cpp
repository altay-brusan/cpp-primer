/*
 * Chapter 10 - RTTI (1/2): typeid for type-tagged dispatch
 *
 * `typeid(x)` returns a `std::type_info` describing the dynamic type of x
 * (when x has a virtual function - otherwise it returns the static type).
 * Two `type_info` values can be compared with `==`.
 *
 * This sample uses typeid as a poor man's dispatch table. In real code, you
 * should reach for virtual functions instead - they're cheaper, faster, and
 * extensible without touching the dispatch site. But typeid does have uses:
 * heterogenous registries, debugging, and the type-erased corners of the
 * Standard Library (`std::any::type()` returns one).
 *
 * Key notes:
 *   - Requires a polymorphic base (`virtual ~Animal() = default;`) for typeid
 *     to see the dynamic type. Without virtuals, typeid returns the static
 *     reference type.
 *   - Header `<typeinfo>` is implicitly pulled in by `<print>` here, but in
 *     general include it explicitly if you use typeid.
 */
#include <print>

using namespace std;

class Animal { public: virtual ~Animal() = default; };
class Dog : public Animal {};
class Bird : public Animal {};

void speak(const Animal& animal)
{
	if (typeid(animal) == typeid(Dog)) {
		println("Woof!");
	} else if (typeid(animal) == typeid(Bird)) {
		println("Chirp!");
	}
}

int main()
{
	speak(Dog{});
	speak(Bird{});
}
