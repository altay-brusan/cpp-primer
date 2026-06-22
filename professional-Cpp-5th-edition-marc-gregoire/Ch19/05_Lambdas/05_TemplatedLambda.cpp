/*
 * Chapter 19 - Templated Lambda Expressions
 *
 * Contrasts two ways of getting at the element type of a vector argument inside a lambda.
 * The first uses a generic (auto) lambda and recovers the type the verbose way, with
 * decay_t<decltype(values)> and the nested value_type alias. The second uses a C++20
 * templated lambda, [] <typename T> (const vector<T>& values), which both constrains the
 * argument to a vector and names its element type T directly - far cleaner.
 *
 * Key notes:
 *   - Templated lambdas also let you require two parameters share one type, e.g.
 *     [] <typename T> (const T& a, const T& b).
 *   - No console output; the bodies only declare a value of the element type.
 */
#include <vector>
#include <type_traits>

using namespace std;

int main()
{
	{
		auto lambda{ [](const auto& values) {
			using V = decay_t<decltype(values)>; // The real type of the vector.
			using T = typename V::value_type;    // The type of the elements of the vector.
			T someValue { };
		} };

		vector values{ 1, 2, 100, 5, 6 };
		lambda(values);
	}

	{
		auto lambda{ [] <typename T> (const vector<T>& values) {
			T someValue{ };
		} };

		vector values{ 1, 2, 100, 5, 6 };
		lambda(values);
	}
}
