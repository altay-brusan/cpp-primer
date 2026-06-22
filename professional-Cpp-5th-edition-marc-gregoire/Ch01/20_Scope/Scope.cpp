/*
 * Chapter 1 - Scope Resolution
 *
 * Every name in C++ lives in some scope. Scopes are created by namespaces, function bodies,
 * classes, and any pair of curly braces. Variables introduced in for/range-for init or in
 * an if/switch init are scoped to that statement. The compiler resolves a bare name by
 * searching outward from the nearest enclosing scope until it finds a match - or fails with
 * an undefined-symbol error.
 *
 * Key notes:
 *   - The "::" scope resolution operator targets a specific scope by name:
 *       NS::get()  - call get() declared inside namespace NS.
 *       ::get()    - call get() declared in the global (unnamed) scope, even if a closer
 *                    name is hiding it.
 *       Demo::get  - reach the member of class Demo (used to define it out of line).
 *   - A name in an inner scope hides identical names in outer scopes. Use "::" to dig out
 *     the hidden one when needed.
 *   - If you put a get() in an unnamed namespace AND there is a global get(), a bare get()
 *     becomes ambiguous. The same can happen with "using namespace X;" if X also has get().
 *   - Lifetime is tied to scope: a local variable is destroyed at the closing brace of its
 *     block. Statics inside functions live until program shutdown but are visible only in
 *     that function.
 */

#include <print>

using namespace std;

class Demo
{
public:
	int get() { return 5; }
};

int get() { return 10; }

namespace NS
{
	int get() { return 20; }
}

int main()
{
	Demo d;
    println("{}", d.get());      // prints 5
    println("{}", NS::get());    // prints 20
    println("{}", ::get());      // prints 10
    println("{}", get());        // prints 10
}
