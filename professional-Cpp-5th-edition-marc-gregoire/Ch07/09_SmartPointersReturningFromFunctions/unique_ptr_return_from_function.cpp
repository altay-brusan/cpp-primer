/*
 * Chapter 7 - Returning Smart Pointers from Functions
 *
 * Smart pointers can be returned from functions by VALUE cheaply and safely. Thanks to
 * (named) return value optimization, (N)RVO, and move semantics, no expensive copy
 * happens at the return site - the compiler either constructs the result directly in the
 * caller's slot or moves it. This makes `unique_ptr<T>` (or `shared_ptr<T>`) the right
 * return type for factory functions that hand out owned objects. Returning a raw owner
 * pointer is a legacy anti-pattern: the caller has no compile-time hint that they must
 * `delete` it.
 *
 * Key notes:
 *   - Return `unique_ptr<T>` for sole-ownership factories; return `shared_ptr<T>` only
 *     when shared ownership is genuinely needed.
 *   - Do NOT `std::move` a local in the `return` statement - it disables NRVO. Just
 *     write `return ptr;`.
 *   - At the call site, the smart pointer can be received by `unique_ptr<T>`, `auto`,
 *     or simply assigned into an existing variable.
 *   - Never return `T*` for ownership: callers will leak it.
 */

#include <print>
#include <memory>

using namespace std;

class Simple
{
public:
	Simple() { println("Simple constructor called!"); }
	~Simple() { println("Simple destructor called!"); }
};

unique_ptr<Simple> create()
{
	auto ptr{ make_unique<Simple>() };
	// Do something with ptr...
	return ptr;        // Plain `return ptr;` - NRVO/move handle the rest. Do NOT std::move here.
}

int main()
{
	unique_ptr<Simple> mySmartPtr1{ create() };  // Direct initialization from factory.
	auto mySmartPtr2{ create() };                // Same thing with auto - common style.
}
