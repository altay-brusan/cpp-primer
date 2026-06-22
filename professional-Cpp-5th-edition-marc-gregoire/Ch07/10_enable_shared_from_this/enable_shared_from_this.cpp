/*
 * Chapter 7 - enable_shared_from_this
 *
 * Inheriting from `std::enable_shared_from_this<T>` (CRTP - the template argument is the
 * derived class itself) lets a member function safely hand out a `shared_ptr<T>` to its
 * own `this`. The base class stashes a hidden `weak_ptr` that the first `make_shared`
 * (or `shared_ptr` ctor) populates; `shared_from_this()` simply locks that `weak_ptr`.
 * This is the ONLY correct way to obtain a `shared_ptr` to `this` - building one
 * directly from `this` creates a second, independent control block and guarantees a
 * double delete.
 *
 * Key notes:
 *   - `shared_from_this()` only works AFTER an owning `shared_ptr` to the object has
 *     been created; calling it earlier (e.g. from the constructor) throws
 *     `std::bad_weak_ptr`.
 *   - `weak_from_this()` is always safe but returns an empty `weak_ptr` before the
 *     first owning `shared_ptr` exists.
 *   - The pattern is mandatory for asynchronous APIs where a callback captures `this`
 *     and needs to keep the object alive until it fires.
 *
 * Example (the WRONG way - do not do this):
 *     shared_ptr<Foo> getPointer() { return shared_ptr<Foo>(this); } // double delete!
 */

#include <memory>

using namespace std;

class Foo : public enable_shared_from_this<Foo>   // CRTP: the template arg is Foo itself.
{
public:
	shared_ptr<Foo> getPointer() {
		return shared_from_this();    // Reuses the existing control block - safe.
	}
};

int main()
{
	auto ptr1{ make_shared<Foo>() };   // Required first: arms the hidden weak_ptr in the base.
	auto ptr2{ ptr1->getPointer() };   // Now safe - ptr1 and ptr2 share the same control block.
}
