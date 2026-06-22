/*
 * Chapter 24 - std::any (a single value of any type)
 *
 * Demonstrates std::any from <any>, a vocabulary type that can hold a single
 * value of essentially any type, with the contained type decided at run time.
 * The sample constructs empty and filled any instances, checks has_value(),
 * inspects the wrapped type via type().name(), and extracts the value with
 * any_cast<T>(), which throws bad_any_cast when the requested type does not
 * match. It also reassigns an any to a different type and stores any objects in
 * a vector to hold heterogeneous data in one container.
 *
 * Key notes:
 *   - Unlike variant, any does not enumerate its types up front.
 *   - The string returned by type().name() is compiler dependent.
 *   - any cannot store references (use pointers or reference_wrapper).
 */

#include <print>
#include <any>
#include <string>
#include <vector>

using namespace std;

int main()
{
	any empty;
	any anInt{ 3 };
	any aString{ "An std::string."s };

	println("empty.has_value = {}", empty.has_value());
	println("anInt.has_value = {}\n", anInt.has_value());

	println("anInt wrapped type = {}", anInt.type().name());
	println("aString wrapped type = {}\n", aString.type().name());

	int theInt{ any_cast<int>(anInt) };
	println("{}", theInt);
	try {
		int test{ any_cast<int>(aString) };
		println("{}", test);
	} catch (const bad_any_cast& ex) {
		println("Exception: {}", ex.what());
	}


	any something{ 3 };              // Now it contains an integer.
	something = "An std::string"s;   // Now the same instance contains a string.


	vector<any> v;
	v.push_back(42);
	v.push_back("An std::string"s);

	println("{}", any_cast<string>(v[1]));
}
