/*
 * Chapter 1 - std::as_const()
 *
 * std::as_const() (in <utility>) returns a reference-to-const to its argument. It is the
 * readable equivalent of "const_cast<const T&>(x)" - cleaner intent and no risk of grabbing
 * the wrong cv-qualifier.
 *
 * Key notes:
 *   - Use it to force a function template or range-based for to dispatch on the const
 *     overload (e.g. "for (auto& e : as_const(c))" yields const references).
 *   - Watch the auto trap: "auto x = as_const(str);" deduces auto to "std::string" and
 *     makes a COPY, throwing away the const&. Either spell the type out as "const auto&" or
 *     "const T&", or use decltype which preserves the qualifiers.
 *   - as_const() is deleted for rvalues - you cannot pass a temporary. That is intentional
 *     (a const-reference to a temporary would dangle).
 */

#include <string>
#include <utility>

using namespace std;

int main()
{
	string str{ "C++" };
	const string& constStr{ as_const(str) };
}
