/*
 * Chapter 1 - std::optional
 *
 * std::optional<T> (in <optional>) holds either a T or nothing. It is the clean way to
 * express "a value that may or may not be present" and replaces sentinel values like -1,
 * nullptr, or EOF as well as the output-parameter-plus-bool-return idiom.
 *
 * Key notes:
 *   - Build an empty optional by returning std::nullopt or simply "{}". A non-empty one is
 *     built from a T directly: "return 42;".
 *   - Test for presence with .has_value() or by using the optional in a boolean context:
 *     "if (opt) { ... }".
 *   - Access the value with .value() (throws std::bad_optional_access if empty) or with
 *     operator* / operator-> (unchecked - undefined behavior on empty).
 *   - .value_or(fallback) returns the value if present, otherwise the fallback.
 *   - You cannot store a reference in an optional - optional<T&> does not work. Store a
 *     pointer (or std::reference_wrapper<T>) instead.
 *   - Useful for optional function arguments and for return types where "no answer" is a
 *     valid outcome rather than an error.
 */

#include <print>
#include <optional>

using namespace std;

optional<int> getData(bool giveIt)
{
	if (giveIt) {
		return 42;
	}

	return nullopt;  // or simply return {};
}

int main()
{
	optional<int> data1{ getData(true) };
	optional<int> data2{ getData(false) };

	println("data1.has_value = {}", data1.has_value());
	if (!data2) {
		println("data2 has no value.");
	}

	println("data1.value = {}", data1.value());
	println("data1.value = {}", *data1);

	try {
		println("data2.value = {}", data2.value());
	} catch (const bad_optional_access& ex) {
		println("Exception: {}", ex.what());
	}

	println("data2.value = {}", data2.value_or(0));
}
