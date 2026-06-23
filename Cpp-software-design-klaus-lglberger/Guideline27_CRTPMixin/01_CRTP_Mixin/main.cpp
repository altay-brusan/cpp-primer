/*
 * Guideline 27 - Use CRTP for Static Mixin Classes
 *                (CRTP as an IMPLEMENTATION pattern: static mixins)
 *
 * In Guideline 26 the book used CRTP as a DESIGN pattern (a static type
 * category, an abstraction accessed through the base). Here CRTP wears its other
 * hat: an IMPLEMENTATION pattern. A base class template injects ready-made
 * operations into a derived value type at compile time, with no runtime cost and
 * no virtual dispatch. This is the use of CRTP that C++20 concepts did NOT make
 * obsolete: concepts can constrain a type, but they cannot synthesize operators
 * for it. For that, CRTP mixins remain "unchallenged" (the book's word).
 *
 * The motivating example is a StrongType: a wrapper that turns a plain T into a
 * distinct, named type (Meter, Kilometer, Surname) so unrelated values cannot be
 * mixed in arithmetic by accident. A bare StrongType is deliberately barren -
 * even adding two Meters will not compile. We want to add operations back, but
 * SELECTIVELY: Meters should be addable, Surnames should not. The solution is to
 * pass each operation as an optional CRTP "skill" mixin in a variadic template
 * template parameter pack. Each skill is a base class template parameterized on
 * the Derived strong type; it contributes operators as hidden friends that are
 * injected into the enclosing namespace and found by argument-dependent lookup.
 *
 * Note what makes this an implementation pattern, not a design pattern: the mixin
 * base classes are PRIVATE, carry no virtual (or protected) destructor, and are
 * never referred to through a base pointer. They are pure implementation detail -
 * convenience and DRY, not abstraction. That is exactly why no polymorphic
 * machinery is needed.
 *
 * Key notes:
 *   - One mixin per operation (Addable, Comparable, Printable, Swappable). Each
 *     is reused unchanged by every derived strong type: DRY, zero duplication.
 *   - Operators are synthesized: Comparable defines operator not-equal in terms
 *     of operator equal-to, so a derived type writes neither by hand.
 *   - Skills are opt-in via a variadic pack, so Meter gets addition while Surname
 *     does not - the static_asserts below prove the selectivity at compile time.
 *   - Meter and Kilometer share the same skills yet stay DISTINCT types: adding a
 *     Meter to a Kilometer still does not compile (strong typing preserved).
 *   - Private base, no virtual destructor: CRTP here is an implementation detail,
 *     so it does not compete with C++20 concepts - it complements them.
 */
#include <iostream>
#include <string>
#include <utility>

// --- CRTP skill mixins: each injects operations into a Derived strong type ---

// Addition: provides combined-assignment and binary plus as hidden friends.
template <typename Derived>
struct Addable
{
    friend Derived& operator+=(Derived& lhs, const Derived& rhs)
    {
        lhs.get() += rhs.get();
        return lhs;
    }
    friend Derived operator+(const Derived& lhs, const Derived& rhs)
    {
        return Derived{lhs.get() + rhs.get()};
    }
};

// Equality: defines operator equal-to, then SYNTHESIZES operator not-equal
// from it, so a derived type never writes the second operator by hand.
template <typename Derived>
struct Comparable
{
    friend bool operator==(const Derived& lhs, const Derived& rhs)
    {
        return lhs.get() == rhs.get();
    }
    friend bool operator!=(const Derived& lhs, const Derived& rhs)
    {
        return !(lhs == rhs); // synthesized from operator equal-to above
    }
};

// Stream output: forwards the wrapped value to the stream.
template <typename Derived>
struct Printable
{
    friend std::ostream& operator<<(std::ostream& os, const Derived& d)
    {
        return os << d.get();
    }
};

// Swapping: swaps the wrapped values, enabling ADL on the underlying type.
template <typename Derived>
struct Swappable
{
    friend void swap(Derived& lhs, Derived& rhs)
    {
        using std::swap; // enable ADL for the wrapped type
        swap(lhs.get(), rhs.get());
    }
};

// --- The StrongType wrapper, parameterized on a variadic pack of skills -------
// It derives PUBLICLY from each requested skill. The skill bases are empty and
// expose no members of their own; their operations are hidden friends, found
// ONLY through argument-dependent lookup (ADL). Public inheritance is required
// for that ADL to work portably: a compiler does not consider an inaccessible
// (private) base among a type's associated classes, so private inheritance can
// hide the hidden-friend operators. The unique Tag still keeps each strong type
// distinct, so public bases do not weaken the abstraction.
template <typename T, typename Tag, template <typename> class... Skills>
struct StrongType : public Skills<StrongType<T, Tag, Skills...>>...
{
    using value_type = T;

    explicit StrongType(const T& value) : value_(value) {}

    T& get() { return value_; }
    const T& get() const { return value_; }

private:
    T value_;
};

// --- Two derived value types reusing the SAME mixins (DRY) --------------------
// Meter and Kilometer are addable, comparable, printable, swappable; the unique
// tag struct (declared right in the parameter list) keeps them distinct types.
template <typename T>
using Meter = StrongType<T, struct MeterTag, Addable, Comparable, Printable, Swappable>;

template <typename T>
using Kilometer = StrongType<T, struct KilometerTag, Addable, Comparable, Printable, Swappable>;

// Surname deliberately OMITS Addable: concatenating two surnames makes no sense.
using Surname = StrongType<std::string, struct SurnameTag, Comparable, Printable, Swappable>;

// Small concepts used only to demonstrate the selectivity at compile time.
template <typename U>
concept HasPlus = requires(U a, U b) { a + b; };

// Whether two (possibly different) types can be combined with binary plus.
// Naming the requirement as a concept keeps its evaluation SFINAE-friendly.
template <typename A, typename B>
concept Combinable = requires(A a, B b) { a + b; };

int main()
{
    // Addable skill: two Meters combine into a Meter.
    const auto m1 = Meter<long>{120L};
    const auto m2 = Meter<long>{50L};
    const auto m3 = m1 + m2;
    std::cout << "m1 + m2 = " << m3 << " m\n"; // Printable skill in action

    auto m4 = Meter<long>{10L};
    m4 += m1; // combined-assignment from the same mixin
    std::cout << "m4 after += m1 = " << m4 << " m\n";

    // Comparable skill: operator equal-to and the synthesized operator not-equal.
    std::cout << "(m1 == m2) -> " << std::boolalpha << (m1 == m2) << '\n';
    std::cout << "(m1 != m2) -> " << (m1 != m2) << '\n';

    // Swappable skill: swap two values via the injected friend swap.
    auto a = Meter<long>{1L};
    auto b = Meter<long>{2L};
    swap(a, b);
    std::cout << "after swap: a = " << a << " m, b = " << b << " m\n";

    // Surname reuses Comparable/Printable/Swappable but NOT Addable.
    const auto s1 = Surname{"Stroustrup"};
    const auto s2 = Surname{"Iglberger"};
    std::cout << "surnames: " << s1 << " vs " << s2
              << "  equal? " << (s1 == s2) << '\n';

    // Compile-time proof of the design's two key guarantees:
    static_assert(HasPlus<Meter<long>>, "Meter opted into Addable");
    static_assert(!HasPlus<Surname>, "Surname did NOT opt into Addable");
    // Distinct strong types never mix, even with identical skills:
    static_assert(!Combinable<Meter<long>, Kilometer<long>>,
                  "Meter and Kilometer remain distinct types");

    std::cout << "\nSkills are opt-in CRTP mixins, synthesized at compile time "
                 "with zero runtime cost.\n";
    return 0;
}
