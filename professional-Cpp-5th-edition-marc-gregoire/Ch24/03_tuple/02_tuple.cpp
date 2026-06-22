/*
 * Chapter 24 - std::tuple basics
 *
 * Demonstrates std::tuple from <tuple>, a generalization of pair that stores any
 * number of values, each with its own compile-time-fixed type. The sample
 * accesses elements with get<index>() and get<T>(), queries element types with
 * tuple_element and the tuple length with tuple_size, and prints the tuple as a
 * whole (C++23 println support). It also uses CTAD to build a tuple, and shows
 * that ref() and cref() (from <functional>) are needed to put reference and
 * reference-to-const elements into a deduced tuple, since & cannot be used there.
 *
 * Key notes:
 *   - get<index>() needs a compile-time index; get<T>() fails to compile if the
 *     type T appears in more than one element.
 *   - tuple_element<I, T>::type and tuple_size<T>::value are compile-time queries
 *     that take the tuple type (use decltype on an instance), not an instance.
 *   - Modifying a ref() element changes the referenced variable; a cref() element
 *     is read-only.
 */

#include <print>
#include <tuple>
#include <string>
#include <typeinfo>
#include <functional> 

using namespace std;

int main()
{
	using MyTuple = tuple<int, string, bool>;
	MyTuple t1{ 16, "Test", true };
	//tuple t1{ 16, "Test"s, true };  // Using CTAD

	// Starting with C++23, println() has full support for tuple.
	println("t1 = {}", t1);
	
	println("t1 = ({}, {}, {})", get<0>(t1), get<1>(t1), get<2>(t1));

	println("Type of get<1>(t1) = {}", typeid(get<1>(t1)).name());

	println("Type of element with index 2 = {}",
		typeid(tuple_element<2, MyTuple>::type).name());

	println("String = {}", get<string>(t1));

	println("Tuple Size = {}", tuple_size<MyTuple>::value);
	println("Tuple Size = {}", tuple_size<decltype(t1)>::value);

	double d{ 3.14 };
	string str1{ "Test" };
	// t2 will be tuple<int, double&, const double&, string&>
	tuple t2{ 16, ref(d), cref(d), ref(str1) };  // Using CTAD
	// Or using make_tuple().
	//auto t2{ make_tuple(16, ref(d), cref(d), ref(str1)) };

	println("d = {}", d);
	get<1>(t2) *= 2;
	//get<2>(t2) *= 2;    // ERROR because of cref().
	println("d = {}", d);
}