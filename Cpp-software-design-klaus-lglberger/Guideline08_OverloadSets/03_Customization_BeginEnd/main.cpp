/*
 * Guideline 8 - Understand the Semantic Requirements of Overload Sets
 *               (overload sets as a generic customization point: begin/end)
 *
 * This sample shows the constructive side of the guideline: a free-function
 * overload set turns ordinary generic code into a customization point that any
 * type can plug into, nonintrusively, through argument dependent lookup (ADL).
 *
 * The book's traverseRange() restricts itself when it calls range.begin() and
 * range.end() as MEMBER functions: that artificial requirement excludes types
 * which cannot have those members, most famously the built-in array. Rewriting
 * it on top of the FREE begin()/end() overload set removes the restriction.
 * Now it works for std::vector (member begin/end adapted by std::begin), for a
 * built-in array (std::begin returns a pointer), and for a custom type that has
 * no members at all but supplies its own free begin()/end() overloads.
 *
 * The enabling trick is again the two-step calling convention:
 *
 *     using std::begin;  using std::end;   // generic fallbacks visible...
 *     for (auto p = begin(r); p != end(r); ++p) ...   // unqualified -> ADL
 *
 * Key notes:
 *   - begin()/end() form an overload set with a clear contract: return a pair
 *     of iterators that traverse the range. The custom Trio honors exactly that
 *     contract, so the generic algorithm just works (no edits to sumRange).
 *   - Extension is nonintrusive and additive: Trio gains range support by
 *     adding two free functions, not by modifying sumRange or any library type.
 *   - Pay attention to conventions: begin()/end() must yield iterators, not
 *     start or stop some process - the name sets the expectation (per the book).
 *   - This is the std::swap idea applied to traversal: one generic algorithm,
 *     many types, all coordinated through a free-function overload set and ADL.
 */
#include <iostream>
#include <iterator> // std::begin, std::end
#include <vector>

namespace coll
{
    // A tiny fixed-size container WITHOUT member begin()/end(). It joins the
    // begin()/end() overload set nonintrusively via two free overloads.
    struct Trio
    {
        int data[3];
    };

    const int* begin(const Trio& t) { return t.data; }
    const int* end(const Trio& t) { return t.data + 3; }
}

// Generic algorithm built on the FREE begin()/end() overload set instead of
// member functions, so it does not impose an artificial requirement on Range.
template <typename Range>
int sumRange(const Range& r)
{
    using std::begin; // two-step convention: generic fallbacks as a baseline...
    using std::end;   // ...then unqualified calls let ADL find custom overloads.

    int total = 0;
    for (auto pos = begin(r); pos != end(r); ++pos)
    {
        total += *pos;
    }
    return total;
}

int main()
{
    int arr[6] = { 4, 8, 15, 16, 23, 42 }; // built-in array: std::begin/end
    std::vector<int> vec{ 1, 2, 3, 4 };     // std::vector: std::begin/end
    coll::Trio trio{ { 10, 20, 30 } };      // custom type: coll::begin/end (ADL)

    std::cout << "Overload set as a customization point: free begin()/end()\n\n";
    std::cout << "sum(arr)  = " << sumRange(arr) << "  (built-in array)\n";
    std::cout << "sum(vec)  = " << sumRange(vec) << "  (std::vector)\n";
    std::cout << "sum(trio) = " << sumRange(trio) << "  (custom Trio via ADL)\n\n";

    std::cout << "One generic sumRange() served all three types. The built-in\n"
                 "array would have failed a member-begin() design, and Trio plugged\n"
                 "in by adding two free functions - no edits to existing code.\n";
    return 0;
}
