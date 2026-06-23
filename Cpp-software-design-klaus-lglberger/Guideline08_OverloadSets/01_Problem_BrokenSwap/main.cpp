/*
 * Guideline 8 - Understand the Semantic Requirements of Overload Sets
 *               (the Problem: an overload that breaks the set's semantics)
 *
 * A free-function overload set (swap, begin, end, size, data, to_string, ...)
 * is a compile-time abstraction and a customization point: anyone can add a
 * free function for a new type, nonintrusively, and generic code will pick it
 * up through argument dependent lookup (ADL). But - exactly like a base class
 * or a concept - an overload set carries a set of SEMANTIC requirements (the
 * LSP). If you join the set you must honor its expected meaning, or callers of
 * generic code that trusts the set will silently get wrong behavior.
 *
 * This is the book's Widget example. Widget wraps two ints, i and j. We supply
 * a custom swap() overload, but implement it badly: it swaps only i and forgets
 * j. Everyone expects swap() to exchange the ENTIRE observable state of both
 * objects. A coworker calling swap() through the normal two-step convention
 * gets a half-swapped object and an hour of debugging - the overload compiled
 * fine and was selected by ADL, but it lied about its semantics.
 *
 * Key notes:
 *   - The overload set is the abstraction; the contract is "swap exchanges the
 *     full state of two objects". This swap() overload joins the set but
 *     violates the contract, so it is an LSP violation at the overload-set level.
 *   - The bug is silent. The code compiles under -W4, ADL happily selects the
 *     broken overload, and only the wrong runtime result reveals the problem.
 *   - Generic code (reset, sort, std::swap-based moves) trusts the contract.
 *     One non-conforming overload poisons every generic algorithm that relies
 *     on it - that is the danger Core Guideline C.163 warns about.
 *   - See 02_Solution_ProperSwap for the overload that honors the semantics and
 *     the correct "using std::swap; swap(a,b);" calling convention.
 */
#include <iostream>
#include <utility> // std::swap

namespace app
{
    struct Widget
    {
        int i;
        int j;
    };

    // BROKEN custom overload: it joins the swap() overload set but exchanges
    // only i, not j. It compiles and is selected by ADL, yet it breaks the
    // semantic contract every caller of swap() relies on.
    void swap(Widget& a, Widget& b)
    {
        using std::swap;
        swap(a.i, b.i);
        // BUG: j is never swapped, so half the state is silently left behind.
    }
}

// A generic helper that trusts the swap() overload set, using the standard
// two-step convention so ADL can find a type's own swap().
template <typename T>
void exchange_state(T& a, T& b)
{
    using std::swap; // bring std::swap into scope as a fallback...
    swap(a, b);      // ...then call unqualified so ADL prefers app::swap.
}

int main()
{
    app::Widget w1{ 1, 11 };
    app::Widget w2{ 2, 22 };

    std::cout << "Problem: an overload that breaks the swap() contract\n\n";
    std::cout << "before: w1=(" << w1.i << "," << w1.j << ")"
              << "  w2=(" << w2.i << "," << w2.j << ")\n";

    exchange_state(w1, w2);

    std::cout << "after : w1=(" << w1.i << "," << w1.j << ")"
              << "  w2=(" << w2.i << "," << w2.j << ")\n\n";

    std::cout << "Expected w1=(2,22) and w2=(1,11), but j was NOT swapped.\n"
                 "The overload compiled and was selected by ADL, yet it violated\n"
                 "the semantic requirement of the swap() overload set.\n";
    return 0;
}
