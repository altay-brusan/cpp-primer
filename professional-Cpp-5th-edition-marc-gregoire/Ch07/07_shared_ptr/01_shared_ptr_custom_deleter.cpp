/*
 * Chapter 7 - shared_ptr / Custom Deleters
 *
 * `std::shared_ptr<T>` (from `<memory>`) supports shared ownership: multiple
 * `shared_ptr` instances can refer to the same resource, and the resource is freed only
 * when the LAST one is destroyed or reset. Reference counting lives in a small "control
 * block" allocated alongside the resource. Unlike `unique_ptr`, a custom deleter for
 * `shared_ptr` is NOT part of the type - you just pass it as the second constructor
 * argument, which makes the syntax dramatically cleaner.
 *
 * Key notes:
 *   - Prefer `std::make_shared<T>(args...)` whenever you do not need a custom deleter -
 *     it allocates the control block AND the object in one contiguous allocation.
 *   - With a custom deleter you must use the constructor form shown here; `make_shared`
 *     does not take a deleter.
 *   - The deleter type is erased into the control block, so `shared_ptr<int>` always has
 *     the same type regardless of which deleter is bound.
 *   - The control block is thread-safe (counts are atomic); the pointee is NOT - you
 *     still need normal synchronization to touch `*ptr` from multiple threads.
 */

#include <memory>

using namespace std;

int* my_alloc(int value)
{
	return new int{ value };
}

void my_free(int* p)
{
	delete p;
}

int main()
{
	// Note: only ONE template argument, no decltype trick - much nicer than unique_ptr.
	shared_ptr<int> myIntSmartPtr{ my_alloc(42), my_free };
}
