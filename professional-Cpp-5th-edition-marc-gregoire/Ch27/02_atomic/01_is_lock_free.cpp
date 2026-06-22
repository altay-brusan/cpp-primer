/*
 * Chapter 27 - Atomic Types: is_lock_free()
 *
 * std::atomic can wrap any trivially copyable type, but whether its operations run
 * without an underlying lock depends on the type and platform. This sample wraps a large
 * Foo (an int array) and a tiny Bar (a single int) in atomics and queries is_lock_free()
 * on each. Both are trivially copyable, yet atomic<Foo> typically is not lock free while
 * atomic<Bar> is, because the small type fits the hardware's atomic instructions.
 */

#include <print>
#include <atomic>
#include <type_traits>

using namespace std;

struct Foo { int m_array[123]; };
struct Bar { int m_int; };

int main()
{
	atomic<Foo> f;
	println("{} {}", is_trivially_copyable_v<Foo>, f.is_lock_free());

	atomic<Bar> b;
	println("{} {}", is_trivially_copyable_v<Bar>, b.is_lock_free());
}
