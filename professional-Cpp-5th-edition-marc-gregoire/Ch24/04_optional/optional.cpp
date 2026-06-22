/*
 * Chapter 24 - std::optional and its monadic operations
 *
 * Demonstrates std::optional from <optional>, the vocabulary type (introduced in
 * Chapter 1) for a value that may or may not be present; Parse() returns an empty
 * optional instead of throwing when stoi() fails. The sample focuses on the C++23
 * monadic chaining operations: and_then() runs the next step only when a value is
 * present, transform() maps the contained value to a new one, and or_else()
 * supplies a fallback when the optional is empty - composing without explicit
 * has_value() checks at each step.
 *
 * Key notes:
 *   - Reads integers from standard input in a loop until EOF or "q", so it needs
 *     interactive input to run.
 */

#include <print>
#include <string>
#include <optional>
#include <iostream>

using namespace std;

optional<int> Parse(const string& str)
{
	try {
		return stoi(str);
	} catch (...) {
		return {};
	}
}

int main()
{
	while (true) {
		print("Enter an integer (q to stop): ");
		string str;
		if (!getline(cin, str) || str == "q") {
			break;
		}

		auto result{ Parse(str)
			.and_then([](int value) -> optional<int> { return value * 2; })
			.transform([](int value) { return to_string(value); })
			.or_else([] { return optional<string>{ "No Integer" }; }) };
		println("    > Result: {}", *result);
	}
}
