/*
 * Chapter 1 - Copy List vs. Direct List Initialization
 *
 * Two brace-init forms look similar but behave differently when combined with "auto":
 *   - Copy list initialization:     auto a = { 11 };    -> std::initializer_list<int>
 *   - Direct list initialization:   auto c { 11 };      -> int
 *
 * Key notes:
 *   - Direct list init with multiple elements is a compile error:
 *         auto d { 11, 22 };   // does not compile
 *     The variable cannot hold more than one value, and auto refuses to deduce it as a list.
 *   - Copy list init requires all elements to share a common type:
 *         auto b = { 11, 22.33 };   // error: mixed types
 *   - Before C++17 both forms produced an initializer_list - the C++17 change made
 *     "auto x { value };" deduce the underlying scalar type instead, which is usually what
 *     you wanted anyway.
 *   - Practical rule: prefer the direct form with one initializer ("auto c { 11 };") for
 *     normal variables. Use the copy form only when you specifically want an
 *     initializer_list (e.g. passing to a function that takes one).
 */

#include <initializer_list>

int main()
{
	// Copy list initialization
	auto a = { 11 };         // initializer_list<int>
	auto b = { 11, 22 };     // initializer_list<int>

	// Direct list initialization
	auto c{ 11 };           // int
	//auto d{ 11, 22 };       // Error, too many elements.
}
