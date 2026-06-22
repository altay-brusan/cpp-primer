/*
 * Chapter 7 - unique_ptr / Creating and Using unique_ptrs
 *
 * `std::unique_ptr<T>` (from `<memory>`) is the default smart pointer for sole ownership:
 * exactly one `unique_ptr` ever owns the resource, and when it is destroyed or reset the
 * resource is automatically freed. This kills the most common leak shapes - early
 * returns, thrown exceptions, and forgotten cleanup all become non-issues, because the
 * destructor runs at scope exit no matter how the function ends.
 *
 * Key notes:
 *   - Prefer `std::make_unique<T>(args...)` over `unique_ptr<T>{ new T{...} }` - it names
 *     `T` only once and is exception-safe in argument lists (before C++17 this mattered
 *     enormously).
 *   - `make_unique` value-initializes; `make_unique_for_overwrite` (C++20) is the
 *     opt-out for hot loops where default initialization is wasted work.
 *   - `.get()` hands out the raw pointer without transferring ownership - use it to call
 *     legacy `T*`-taking APIs.
 *   - `.reset()` (no args) frees and sets to `nullptr`; `.reset(p)` frees and adopts `p`.
 *   - `.release()` hands the raw pointer back to you AND clears the smart pointer; from
 *     that point you are personally responsible for calling `delete`.
 *   - CTAD does NOT work for `unique_ptr` - you must always spell the template argument.
 *   - `unique_ptr` is move-only - it cannot be copied. See `02_unique_ptr_move.cpp`.
 *
 * Example:
 *     auto p = std::make_unique<Simple>();      // preferred
 *     std::unique_ptr<Simple> p{ new Simple{} }; // works, but mentions Simple twice
 */

#include <print>
#include <memory>

using namespace std;

class Simple
{
public:
	Simple() { println("Simple constructor called!"); }
	~Simple() { println("Simple destructor called!"); }

	void go() {}
};


void leaky()
{
	Simple* mySimplePtr{ new Simple{} };  // BUG! No matching delete - guaranteed leak.
	mySimplePtr->go();
}


void couldBeLeaky()
{
	Simple* mySimplePtr{ new Simple{} };
	mySimplePtr->go();                    // If go() throws, the next line never runs.
	delete mySimplePtr;                   // Still a latent leak under exceptions.
}


void notLeaky()
{
	auto mySimpleSmartPtr{ make_unique<Simple>() };  // ctor + dtor handled automatically
	mySimpleSmartPtr->go();
}                                                    // dtor frees Simple here - even on throw


void processData(Simple* simple)
{
	/* Use the simple pointer ... */
	simple->go();
}

int main()
{
	leaky();
	couldBeLeaky();
	notLeaky();

	unique_ptr<Simple> mySimpleSmartPtr{ new Simple{} };  // direct ctor form - mentions Simple twice

	processData(mySimpleSmartPtr.get());  // .get() exposes the raw pointer; no ownership transfer

	mySimpleSmartPtr.reset();             // Free resource and set to nullptr
	mySimpleSmartPtr.reset(new Simple{}); // Free old resource and adopt a new one

	Simple* simple{ mySimpleSmartPtr.release() }; // Detach: smart ptr becomes nullptr,
	                                              // you now OWN the raw pointer.
	// Use the simple pointer...
	delete simple;                        // ...and you are responsible for delete.
	simple = nullptr;
}