/*
 * Chapter 7 - weak_ptr
 *
 * `std::weak_ptr<T>` is a non-owning observer that tracks an object managed by a
 * `shared_ptr`. It does NOT increment the reference count, so its existence will not
 * keep the object alive. To touch the underlying resource you must first promote the
 * `weak_ptr` to a `shared_ptr` with `.lock()` - this returns an empty `shared_ptr` if
 * the resource has already been freed, giving you a safe test for "is this still
 * around?". The primary use cases are caches and breaking reference cycles between
 * `shared_ptr` instances.
 *
 * Key notes:
 *   - `.lock()` is the safe path - it never throws and returns `nullptr` on a dead
 *     resource. Constructing a `shared_ptr` directly from a `weak_ptr` throws
 *     `std::bad_weak_ptr` if the resource is gone.
 *   - Two `shared_ptr`s pointing at each other create a cycle that never reaches a
 *     zero refcount; replacing one with a `weak_ptr` breaks the cycle.
 *   - A `weak_ptr` can only be constructed from a `shared_ptr` (or another `weak_ptr`).
 *   - The control block lives as long as ANY `shared_ptr` OR `weak_ptr` exists, even
 *     though the managed object dies with the last `shared_ptr`.
 *
 * Example:
 *     if (auto sp = wp.lock()) { sp->go(); }   // common safe-use idiom
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

void useResource(weak_ptr<Simple>& weakSimple)
{
	auto resource{ weakSimple.lock() };   // Promote to shared_ptr (or get empty one).
	if (resource) {                       // Truthiness checks for a non-null shared_ptr.
		println("Resource still alive.");
	} else {
		println("Resource has been freed!");
	}
}

int main()
{
	auto sharedSimple{ make_shared<Simple>() };
	weak_ptr<Simple> weakSimple{ sharedSimple };   // Non-owning - shared count stays at 1.

	// Try to use the weak_ptr.
	useResource(weakSimple);

	// Reset the shared_ptr.
	// Since there is only 1 shared_ptr to the Simple resource, this will
	// free the resource, even though there is still a weak_ptr alive.
	sharedSimple.reset();   // Last shared_ptr gone -> Simple destroyed, weakSimple expires.

	// Try to use the weak_ptr a second time.
	useResource(weakSimple);
}
