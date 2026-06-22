/*
 * Chapter 26 - The conditional Type Trait
 *
 * Implements move_assign_if_noexcept(), a counterpart to the Standard Library's
 * move_if_noexcept(). It uses conditional_t together with
 * is_nothrow_move_assignable_v to choose the return type: an rvalue reference
 * when the type's move assignment is noexcept, otherwise a reference-to-const,
 * so a throwing move is silently downgraded to a copy.
 *
 * Key notes:
 *   - conditional picks one of two types based on a compile-time Boolean; the
 *     _t alias avoids writing a trailing ::type.
 */

#include <print>
#include <type_traits>
#include <utility>

using namespace std;

template <typename T>
constexpr conditional_t<is_nothrow_move_assignable_v<T>, T&&, const T&>
move_assign_if_noexcept(T& t) noexcept
{
	return std::move(t);
}

class MoveAssignable
{
public:
	MoveAssignable& operator=(const MoveAssignable&)
	{
		println("copy assign");
		return *this;
	}
	MoveAssignable& operator=(MoveAssignable&&)
	{
		println("move assign");
		return *this;
	}
};

class MoveAssignableNoexcept
{
public:
	MoveAssignableNoexcept& operator=(const MoveAssignableNoexcept&)
	{
		println("copy assign");
		return *this;
	}
	MoveAssignableNoexcept& operator=(MoveAssignableNoexcept&&) noexcept
	{
		println("move assign");
		return *this;
	}
};

int main()
{
	MoveAssignable a, b;
	a = move_assign_if_noexcept(b);
	MoveAssignableNoexcept c, d;
	c = move_assign_if_noexcept(d);
}
