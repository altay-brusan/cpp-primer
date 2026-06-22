/*
 * Chapter 12 - auto vs decltype(auto)
 *
 * Four ways to capture the result of `getString()`, which returns
 * `const std::string&`. Each has a subtly different type:
 *
 *   - `auto s1{ getString() };`
 *       Drops the reference, drops const -> `std::string`. Copies the message.
 *
 *   - `const auto& s2{ getString() };`
 *       Explicit reference + const -> `const std::string&`. Aliases the message.
 *
 *   - `decltype(getString()) s3{ getString() };`
 *       Preserves whatever getString's *declared* return type is -> `const std::string&`.
 *
 *   - `decltype(auto) s4{ getString() };`
 *       Special form: deduce the type the same way decltype would on the
 *       initializer expression. Preserves both reference-ness and const.
 *       Result: `const std::string&`. Aliases the message.
 *
 * Key notes:
 *   - `auto` is "value-like": copies, strips refs and top-level const.
 *   - `decltype(auto)` is "exact-like": keeps refs, keeps const.
 *   - Use plain `auto` by default. Reach for `decltype(auto)` only when
 *     you specifically need to preserve a reference, like in a generic
 *     wrapper that should perfectly forward the return type.
 */
#include <string>

const std::string message{ "Test" };

const std::string& getString()
{
	return message;
}

int main()
{
	auto s1{ getString() };
	const auto& s2{ getString() };
	decltype(getString()) s3{ getString() };
	decltype(auto) s4{ getString() };
}
