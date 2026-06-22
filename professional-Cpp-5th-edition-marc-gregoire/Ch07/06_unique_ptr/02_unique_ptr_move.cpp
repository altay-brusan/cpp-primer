/*
 * Chapter 7 - unique_ptr / Move Semantics
 *
 * A `unique_ptr` represents UNIQUE ownership, so it cannot be copied - the copy
 * constructor and copy assignment are deleted. To transfer ownership, you MOVE it with
 * `std::move`. After the move, the source `unique_ptr` is empty (holds `nullptr`) and the
 * destination owns the resource. This is the pattern used to thread a `unique_ptr`
 * through constructors, function arguments, and return values.
 *
 * Key notes:
 *   - `std::move` does not actually move anything - it casts to an rvalue reference so
 *     the move constructor/assignment is selected.
 *   - Move semantics are covered in detail in Chapter 9; for now treat `move(p)` as
 *     "hand ownership over to whoever is on the receiving side."
 *   - A constructor taking `unique_ptr<T>` by value is the idiomatic way to accept an
 *     owning argument - the caller is forced to `move` or `make_unique` at the call site.
 *   - After `Foo f{ move(myIntSmartPtr) };` the local `myIntSmartPtr` is empty; using it
 *     would be valid but pointless (it owns nothing).
 */

#include <memory>
#include <utility>

using namespace std;

class Foo
{
public:
	Foo(unique_ptr<int> data) : m_data{ move(data) } { }  // by-value param + move into member
	                                                      // is the canonical sink-argument idiom
private:
	unique_ptr<int> m_data;
};

int main()
{
	auto myIntSmartPtr{ make_unique<int>(42) };
	Foo f{ move(myIntSmartPtr) };          // After this line, myIntSmartPtr is empty (nullptr).
}
