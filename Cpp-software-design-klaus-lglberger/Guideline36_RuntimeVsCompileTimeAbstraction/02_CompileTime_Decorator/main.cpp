/*
 * Guideline 36 - Understand the Trade-off Between Runtime and Compile Time Abstraction
 *                (the COMPILE TIME, value-based Decorator built with templates)
 *
 * This file is the COMPILE TIME end of the same design space. The very same
 * Decorator pattern is expressed entirely with class templates, so the whole
 * decoration stack becomes part of the TYPE: Taxed of Discounted of
 * ConferenceTicket. Nothing about the stack is decided at run time, which is the
 * limitation; in exchange there is not one virtual call and not one heap
 * allocation, so the compiler can inline the entire price() computation.
 *
 * A C++20 concept, PricedItem, plays the role the Item base class plays in the
 * classic Decorator: it states the requirement (a price member) that every
 * decorated type must satisfy. Discounted decorates by composition (Guideline 20)
 * and Taxed decorates by private inheritance, two valid ways to model the same
 * Decorator relationship. The discount and tax rates are non-type template
 * parameters, so each distinct rate yields a distinct type.
 *
 * Key notes:
 *   - Compile time abstraction: the stack Taxed of Discounted of X is a TYPE, so
 *     it is fixed when the program is built and cannot vary at run time.
 *   - Zero overhead: no base class, no virtual call, no pimpl allocation, so the
 *     compiler inlines every layer and folds price() into a few multiplications.
 *   - The PricedItem concept is the abstraction that any new item or Decorator
 *     must satisfy, mirroring the base class of the classic pattern and serving
 *     the same OCP and DIP roles.
 *   - Cost of the trade: each distinct rate is a new type, so combinations grow
 *     code and build time, all class templates live in headers, and the lack of
 *     a common base means each stack needs its own container.
 *   - Same result as the runtime version, but every choice is frozen at compile
 *     time. Real designs usually land somewhere between the two ends.
 */
#include <concepts>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

// A tiny value type standing in for the book Money type.
struct Money
{
    double amount{};
};

constexpr Money operator*(Money m, double factor) { return Money{m.amount * factor}; }
constexpr Money operator+(Money a, Money b) { return Money{a.amount + b.amount}; }
std::ostream& operator<<(std::ostream& os, Money m) { return os << m.amount; }

// A plain, value-based priced thing: no base class, no virtual functions.
class ConferenceTicket
{
public:
    ConferenceTicket(std::string name, Money price)
        : m_name(std::move(name)), m_price(price)
    {
    }

    const std::string& name() const { return m_name; }
    Money price() const { return m_price; }

private:
    std::string m_name;
    Money m_price;
};

// The abstraction: every decorated type must expose a price member returning
// Money. This concept is the compile time equivalent of the Item base class.
template <typename T>
concept PricedItem = requires(const T item) {
    { item.price() } -> std::same_as<Money>;
};

// Decorator by composition: stores the wrapped item as a member.
template <double discount, PricedItem Item>
class Discounted
{
public:
    template <typename... Args>
    explicit Discounted(Args&&... args) : m_item{std::forward<Args>(args)...}
    {
    }

    Money price() const { return m_item.price() * (1.0 - discount); }

private:
    Item m_item;
};

// Decorator by private inheritance: an equally valid way to model the relation.
template <double taxRate, PricedItem Item>
class Taxed : private Item
{
public:
    template <typename... Args>
    explicit Taxed(Args&&... args) : Item{std::forward<Args>(args)...}
    {
    }

    Money price() const { return Item::price() * (1.0 + taxRate); }
};

int main()
{
    // The whole decoration stack is the TYPE. 20% discount, then 15% tax:
    // (499 * 0.8) * 1.15 = 459.08
    Taxed<0.15, Discounted<0.2, ConferenceTicket>> item{"Core C++", Money{499.0}};
    std::cout << "One composed stack, price = " << item.price() << '\n';

    // Each combination is its own distinct type, fixed at compile time.
    using Plain = ConferenceTicket;
    using DiscountedTicket = Discounted<0.2, ConferenceTicket>;
    using TaxedDiscountedTicket = Taxed<0.19, Discounted<0.2, ConferenceTicket>>;

    // Because the stacks have no common base, each type needs its own container.
    std::vector<DiscountedTicket> discounted;
    discounted.emplace_back("Member A", Money{100.0});
    discounted.emplace_back("Member B", Money{250.0});

    Money total{};
    for (const DiscountedTicket& t : discounted)
        total = total + t.price();
    std::cout << "Two DiscountedTicket items, total = " << total << '\n';

    Plain plain{"Basic", Money{100.0}};
    TaxedDiscountedTicket stacked{"Full", Money{100.0}};
    std::cout << "Plain price = " << plain.price()
              << ", stacked price = " << stacked.price() << '\n';

    std::cout << "\nEvery decoration is baked into the type at compile time:\n"
                 "no virtual calls, no allocations, fully inlinable. The cost is\n"
                 "zero runtime flexibility and a new type per rate combination.\n";
    return 0;
}
