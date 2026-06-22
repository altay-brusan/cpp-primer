/*
 * Chapter 7 - shared_ptr / Aliasing
 *
 * A `shared_ptr` actually tracks TWO pointers: the "owned" pointer used for reference
 * counting, and the "stored" pointer returned by `get()` and `operator*`. The aliasing
 * constructor lets you share ownership of one object while exposing a pointer to a
 * different (typically sub-)object. The common use case is pointing at a member of a
 * larger object that the outer `shared_ptr` keeps alive.
 *
 * Key notes:
 *   - Form: `shared_ptr<U>{ outer_sp, &outer_sp->member }`. The outer `shared_ptr` keeps
 *     the parent alive; the new `shared_ptr<U>` exposes only the member.
 *   - The parent is destroyed only when EVERY participating `shared_ptr` (including the
 *     aliasing one) is gone.
 *   - The stored pointer can be any address whose lifetime is bound to the owned object -
 *     a member, a subobject in an inheritance hierarchy, an element in an owned array.
 *   - Useful for handing out a "view" pointer to a piece of state without leaking the
 *     whole containing object's type.
 */

#include <memory>

using namespace std;

class Foo
{
public:
	Foo(int value) : m_data{ value } { }
	int m_data;
};

int main()
{
	auto foo{ make_shared<Foo>(42) };
	// Aliasing ctor: shares foo's control block (and thus its lifetime) but exposes
	// the address of foo->m_data. The Foo dies only when BOTH `foo` and `aliasing` are gone.
	auto aliasing{ shared_ptr<int>{ foo, &foo->m_data } };
}