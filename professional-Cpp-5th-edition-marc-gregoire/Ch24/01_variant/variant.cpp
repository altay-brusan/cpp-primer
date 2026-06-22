/*
 * Chapter 24 - std::variant (a type-safe tagged union)
 *
 * Demonstrates std::variant from <variant>, a vocabulary type that holds a
 * single value of one of a fixed set of distinct types. The alternative types
 * must be unique, and a default-constructed variant holds a default-constructed
 * value of its first type; std::monostate is used here as a well-behaved empty
 * first alternative so a variant of non-default-constructible types can still be
 * default constructed. The sample stores different types by assignment, queries
 * the active alternative, retrieves values, and dispatches with a visitor.
 *
 * Key notes:
 *   - index() gives the zero-based active type; holds_alternative<T>() tests it.
 *   - get<index>() or get<T>() throw bad_variant_access on a type mismatch;
 *     get_if<T>(and-pointer) returns nullptr instead of throwing.
 *   - visit() applies a callable (a generic lambda or a visitor object with one
 *     overloaded call operator per alternative) to the currently stored value.
 *   - A variant cannot hold arrays or references (use pointers or reference_wrapper).
 */

#include <print>
#include <variant>
#include <string>

using namespace std;

class Foo { public: Foo() = delete; Foo(int) {} };
class Bar { public: Bar() = delete; Bar(int) {} };

class MyVisitor
{
public:
	static void operator()(int i) { println("int: {}", i); }
	static void operator()(const string& s) { println("string: {}", s); }
	static void operator()(float f) { println("float: {}", f); }
};

int main()
{
	variant<monostate, Foo, Bar> v0;

	variant<int, string, float> v;
	v = 12;
	v = 12.5f;
	v = "An std::string"s;

	println("Type index: {}", v.index());
	println("Contains an int: {}", holds_alternative<int>(v));

	println("{}", get<string>(v));
	try {
		println("{}", get<0>(v));
	} catch (const bad_variant_access& ex) {
		println("Exception: {}", ex.what());
	}

	string* theString{ get_if<string>(&v) };
	int* theInt{ get_if<int>(&v) };
	println("Retrieved string: {}", (theString ? *theString : "n/a"));
	println("Retrieved int: {}", (theInt ? to_string(*theInt) : "n/a"));

	visit([](auto&& value) { println("Value = {}", value); }, v);

	visit(MyVisitor{}, v);
}
