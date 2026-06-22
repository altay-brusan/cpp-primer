/*
 * Chapter 9 - Rvalue References (decay-copy with auto{...})
 *
 * `auto{ expr }` (C++23) materializes a fresh prvalue by copying its argument. The
 * resulting temporary is an rvalue, so it binds to the `string&&` overload without
 * forcing the caller to write `std::move`.
 *
 * Key notes:
 *   - `handleMessage(value)` would fail because the only overload takes `string&&`
 *     and `value` is a named lvalue.
 *   - `handleMessage(auto{ value })` performs a decay-copy: a temporary `string` is
 *     produced and that temporary binds to `string&&`. The original `value` is left
 *     untouched.
 *   - This is sometimes called the decay-copy idiom and replaces older patterns like
 *     `handleMessage(string{ value })`.
 */
#include <print>
#include <string>

using namespace std;

// rvalue reference parameter
void handleMessage(string&& message)
{
	println("handleMessage with rvalue reference: {}", message);
}

int main()
{
	string value{ "Hello " };
	handleMessage(auto{ value });
}