/*
 * Chapter 1 - Type Inference (auto, auto&, auto*)
 *
 * "auto" tells the compiler to deduce a variable's type from its initializer. It saves
 * typing for complex types and decouples code from exact type names, but it has subtle
 * rules around references and const.
 *
 * Key notes:
 *   - Bare "auto" STRIPS reference and const qualifiers. "auto f = foo();" copies the
 *     result even if foo() returned "const std::string&". To preserve the reference, write
 *     "const auto& f = foo();" or "auto& f = foo();".
 *   - The same trap bites std::as_const(): "auto x = as_const(str);" deduces std::string
 *     and makes a copy.
 *   - decltype, by contrast, preserves references and const exactly. "decltype(foo()) f =
 *     foo();" keeps "const std::string&".
 *   - For pointers, "auto* p = &i;" is preferred over plain "auto p = &i;" - it states
 *     pointerness up front and behaves intuitively with const.
 *   - Const + pointer placement matters:
 *         const auto  p1 = &i;   // int* const  (const pointer to non-const int!)
 *         auto const  p2 = &i;   // int* const  (same)
 *         const auto* p3 = &i;   // const int*  (pointer to const int)
 *         auto* const p4 = &i;   // int* const  (const pointer to non-const int)
 *         const auto* const p5 = &i;  // const int* const (both const)
 *   - auto also works for function return types ("auto add(...) { ... }") and structured
 *     bindings ("auto [a, b] = pair;"). These are covered in their own samples.
 */

#include <string>
#include <utility>

using namespace std;

const string message{ "Test" };
const string& foo() { return message; }

int main()
{
	auto x{ 123 };                // x is of type int

	auto f1{ foo() };             // f1 is of type string
	const auto& f2{ foo() };      // f2 is of type const string&

	string str{ "C++" };
	auto result{ as_const(str) }; // result is of type string!


	int i{ 123 };
	//auto p{ &i };               // p is of type int*
	auto* p{ &i };                // p is of type int*
	
	const auto p1{ &i };          // p1 is of type int* const
	auto const p2{ &i };          // p2 is of type int* const 
	const auto* p3{ &i };         // p3 is of type const int*
	auto* const p4{ &i };         // p4 is of type int* const
	const auto* const p5{ &i };   // p5 is of type const int* const
}
