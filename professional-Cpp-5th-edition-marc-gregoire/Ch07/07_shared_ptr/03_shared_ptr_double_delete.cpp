/*
 * Chapter 7 - The Need for Reference Counting
 *
 * `shared_ptr` uses reference counting to decide when to free its resource: every copy
 * bumps the count, every destruction or `reset` drops it, and the resource dies when the
 * count reaches zero. This eliminates double-deletion - as long as you only ever COPY
 * existing `shared_ptr` instances. The reference-counted machinery cannot rescue you if
 * you construct two INDEPENDENT `shared_ptr`s from the same raw pointer: each one
 * believes it is the sole controller and both will call `delete`.
 *
 * Key notes:
 *   - `make_shared<T>(...)` is the safest creation route because no raw pointer ever
 *     escapes - there is nothing for a second `shared_ptr` to latch onto.
 *   - `shared_ptr<T> p2{ p1 }` (copy from another `shared_ptr`) shares the control block;
 *     `shared_ptr<T> p2{ p1.get() }` (copy from a raw pointer) does NOT - that is the bug.
 *   - The same hazard exists for `unique_ptr` constructed from a raw pointer that is
 *     already owned somewhere.
 *   - `.use_count()` exists for debugging; do not branch on it in production code.
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

void doubleDelete()
{
	Simple* mySimple{ new Simple{} };
	shared_ptr<Simple> smartPtr1(mySimple);   // First control block - count = 1.
	shared_ptr<Simple> smartPtr2(mySimple);   // SECOND, independent control block - count = 1.
}                                             // Both will call delete on the same raw pointer.

void noDoubleDelete()
{
	auto smartPtr1{ make_shared<Simple>() };  // Single control block, count = 1.
	auto smartPtr2{ smartPtr1 };              // Copy of the shared_ptr - count = 2.
}                                             // Resource freed exactly once when count hits 0.

int main()
{
	//doubleDelete();  // BUG, might cause a crash!
	noDoubleDelete();
}
