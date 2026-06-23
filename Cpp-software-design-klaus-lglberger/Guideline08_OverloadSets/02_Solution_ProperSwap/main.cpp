/*
 * Guideline 8 - Understand the Semantic Requirements of Overload Sets
 *               (the Solution: a swap() overload that honors the contract)
 *
 * Same Widget as the Problem sample, but now the custom swap() overload joins
 * the swap() overload set correctly: it exchanges the FULL observable state of
 * both objects. Because a free overload is nonintrusive, we extend the behavior
 * of swap() for a brand new type without modifying any existing code - the
 * Open-Closed Principle in action - while still respecting the semantics every
 * caller expects (the LSP for overload sets).
 *
 * The sample also demonstrates the canonical two-step calling convention the
 * book insists on:
 *
 *     using std::swap;   // make the generic std::swap visible as a fallback
 *     swap(a, b);        // unqualified call, so ADL can prefer app::swap
 *
 * Calling std::swap(a,b) fully qualified would defeat the customization point:
 * it would ignore the type's own, possibly more efficient or more correct,
 * overload. Calling swap(a,b) with no using-declaration would fail for types
 * (like the built-in int below) that rely on the std:: version. The two-step
 * form is what makes the overload set a true customization point.
 *
 * Key notes:
 *   - The fixed swap() exchanges both i and j: the overload now satisfies the
 *     semantic requirement of the set, so generic code can trust it.
 *   - exchange_state() is generic and unchanged: it works for Widget (via the
 *     ADL-found app::swap) AND for int (via the std::swap fallback). One
 *     algorithm, many types - the power of a compile-time abstraction.
 *   - Extension was purely additive: no existing function was edited to teach
 *     swap() about Widget. That is the OCP benefit of free-function overloading.
 *   - Pay attention to existing names and conventions: a function named swap()
 *     must swap; one named begin() must yield a traversable iterator, and so on.
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

    // CORRECT custom overload: it joins the swap() overload set and honors the
    // contract by exchanging the complete observable state of both Widgets.
    void swap(Widget& a, Widget& b) noexcept
    {
        using std::swap;
        swap(a.i, b.i);
        swap(a.j, b.j);
    }
}

// Unchanged generic helper: it trusts the swap() overload set and uses the
// two-step convention so the right overload is chosen for any type.
template <typename T>
void exchange_state(T& a, T& b)
{
    using std::swap; // fallback for types without a custom swap (e.g. int)...
    swap(a, b);      // ...ADL prefers app::swap for Widget.
}

int main()
{
    std::cout << "Solution: an overload that honors the swap() contract\n\n";

    app::Widget w1{ 1, 11 };
    app::Widget w2{ 2, 22 };

    std::cout << "before: w1=(" << w1.i << "," << w1.j << ")"
              << "  w2=(" << w2.i << "," << w2.j << ")\n";

    exchange_state(w1, w2); // ADL selects app::swap, which swaps both fields.

    std::cout << "after : w1=(" << w1.i << "," << w1.j << ")"
              << "  w2=(" << w2.i << "," << w2.j << ")\n";
    std::cout << "Full state swapped, as the swap() contract requires.\n\n";

    // The SAME generic helper also works for a plain int, falling back to
    // std::swap - proof that the overload set is one uniform abstraction.
    int a = 7;
    int b = 9;
    std::cout << "before: a=" << a << "  b=" << b << '\n';
    exchange_state(a, b);
    std::cout << "after : a=" << a << "  b=" << b << '\n';

    return 0;
}
