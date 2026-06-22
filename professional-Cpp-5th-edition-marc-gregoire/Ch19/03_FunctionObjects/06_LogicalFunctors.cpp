/*
 * Chapter 19 - Logical Function Objects
 *
 * Uses the predefined logical function objects from <functional>. allTrue() folds a
 * vector<bool> with logical_and<> starting from true, and anyTrue() folds with
 * logical_or<> starting from false, both via the generic accumulateData() helper. This
 * shows logical operators being passed around as callable objects.
 *
 * Key notes:
 *   - The Standard Library's all_of() and any_of() are preferred in practice because
 *     they short-circuit; these functors always visit every element.
 *   - Reads flags from cin until -1, so it needs interactive input to run.
 */
#include <print>
#include <vector>
#include <functional>
#include <iostream>

using namespace std;

template <input_iterator Iter, copy_constructible StartValue,
	invocable<const StartValue&, const StartValue&> Operation>
auto accumulateData(Iter begin, Iter end, const StartValue& startValue, Operation op)
{
	auto accumulated{ startValue };
	for (Iter iter{ begin }; iter != end; ++iter) {
		accumulated = op(accumulated, *iter);
	}
	return accumulated;
}

bool allTrue(const vector<bool>& flags)
{
	return accumulateData(begin(flags), end(flags), true, logical_and<>{});
}

bool anyTrue(const vector<bool>& flags)
{
	return accumulateData(begin(flags), end(flags), false, logical_or<>{});
}

int main()
{
	vector<bool> myVector;
	while (true) {
		print("Enter a value 0 or 1 to add (-1 to stop): ");
		int value;
		cin >> value;
		if (value == -1) {
			break;
		}
		myVector.push_back(value == 1);
	}

	println("allTrue? {}", allTrue(myVector));
	println("anyTrue? {}", anyTrue(myVector));
}
