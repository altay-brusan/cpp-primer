/*
 * Chapter 19 - Arithmetic and Transparent Operator Function Objects
 *
 * Demonstrates the predefined arithmetic function objects from <functional>. A plus<int>
 * instance is called directly, then the multiplies functor is passed as a callback to a
 * generic accumulateData() to compute a geometric mean. The example contrasts the
 * non-transparent multiplies<int> against the transparent multiplies<> (short for
 * multiplies<void>), which deduces operand and result types at the call site. With a
 * double start value (1.1) over an int vector, the transparent functor preserves the
 * double result while the typed one truncates to int.
 *
 * Key notes:
 *   - Prefer the transparent operator functors; they are heterogeneous and avoid narrowing.
 *   - Reads scores from cin until 0 is entered, so it needs interactive input to run.
 */
#include <print>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <span>

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

double geometricMean(span<const int> values)
{
	auto mult{ accumulateData(cbegin(values), cend(values), 1, multiplies<int>{}) };
	return pow(mult, 1.0 / values.size());
}

// Using transparent operator functor
double geometricMeanTransparent(span<const int> values)
{
	auto mult{ accumulateData(cbegin(values), cend(values), 1, multiplies<>{}) };
	return pow(mult, 1.0 / values.size());
}

int main()
{
	plus<int> myPlus;
	int res{ myPlus(4, 5) };
	println("{}", res);

	vector<int> myVector;

	while (true) {
		print("Enter a test score to add (0 to stop): ");
		int score;
		cin >> score;
		if (score == 0) {
			break;
		}
		myVector.push_back(score);
	}

	println("The geometric mean is {}", geometricMean(myVector));
	println("The geometric mean is (transparent function object) {}",
		geometricMeanTransparent(myVector));

	{
		vector<int> values{ 1, 2, 3 };
		double result{ accumulateData(cbegin(values), cend(values), 1.1, multiplies<>{}) };
		println("{}", result);
	}

	{
		vector<int> values{ 1, 2, 3 };
		double result{
			accumulateData(cbegin(values), cend(values), 1.1, multiplies<int>{}) };
		println("{}", result);
	}
}
