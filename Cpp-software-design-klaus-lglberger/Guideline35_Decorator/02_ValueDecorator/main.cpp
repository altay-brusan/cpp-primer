/*
 * Guideline 35 - Use Decorators to Add Customization Hierarchically
 *                (a value-based, compile-time Decorator)
 *
 * Concern: the classic Decorator in sample 01 is correct but pays for its
 * flexibility with reference semantics, lots of pointers, nullptr checks, the
 * danger of dangling pointers, manual lifetime management via unique_ptr, and
 * one virtual call per layer. The book closes the guideline by noting you still
 * have an ace up your sleeve: implement Decorators with VALUE semantics.
 *
 * Here the same wrapping idea is expressed with class templates that store the
 * wrapped item BY VALUE. Taxed<Item> and Discounted<Item> each contain an Item
 * and add behavior in price(). Because the wrapped type is a template parameter,
 * the composition Taxed<Discounted<ConferenceTicket>> is built at compile time:
 * no base class, no heap, no virtual dispatch. A small PricedItem concept states
 * the single requirement, that the wrapped thing has a price(), and the
 * decorators satisfy it themselves, so they stack recursively just like before.
 *
 * Key notes:
 *   - Composition is the same as the GoF version, but each layer is a value held
 *     inside the next: nothing is allocated and price() inlines through the stack.
 *   - The concept makes the wrapper requirement explicit and keeps the templates
 *     honest: anything with a price() returning Money can be wrapped.
 *   - The trade-off versus sample 01: no runtime swapping and a distinct type per
 *     composition, in exchange for speed and value semantics. It depends.
 *   - Stacking order still matters; it is fixed in the type the moment you nest.
 */
#include <cmath>
#include <concepts>
#include <format>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

struct Money
{
    double amount{};
};

Money operator*(Money m, double factor) { return Money{m.amount * factor}; }
Money operator+(Money lhs, Money rhs) { return Money{lhs.amount + rhs.amount}; }

std::string show(Money m) { return std::format("{:.2f}", m.amount); }

// The single structural requirement of a priced item.
template <typename T>
concept PricedItem = requires(const T& t) {
    { t.price() } -> std::convertible_to<Money>;
};

// Concrete leaf items: plain value types, no base class.
class CppBook
{
public:
    CppBook(std::string title, Money price) : m_title(std::move(title)), m_price(price) {}

    const std::string& title() const { return m_title; }
    Money price() const { return m_price; }

private:
    std::string m_title;
    Money m_price;
};

class ConferenceTicket
{
public:
    ConferenceTicket(std::string name, Money price) : m_name(std::move(name)), m_price(price) {}

    const std::string& name() const { return m_name; }
    Money price() const { return m_price; }

private:
    std::string m_name;
    Money m_price;
};

// Value-based decorators. Each holds the wrapped item by value and itself models
// PricedItem, so decorators nest at compile time.
template <PricedItem Item>
class Discounted
{
public:
    Discounted(double discount, Item item) : m_factor(1.0 - discount), m_item(std::move(item))
    {
        if (!std::isfinite(discount) || discount < 0.0 || discount > 1.0)
            throw std::invalid_argument("Invalid discount");
    }

    Money price() const { return m_item.price() * m_factor; }

private:
    double m_factor;
    Item m_item;
};

template <PricedItem Item>
class Taxed
{
public:
    Taxed(double taxRate, Item item) : m_factor(1.0 + taxRate), m_item(std::move(item))
    {
        if (!std::isfinite(taxRate) || taxRate < 0.0)
            throw std::invalid_argument("Invalid tax");
    }

    Money price() const { return m_item.price() * m_factor; }

private:
    double m_factor;
    Item m_item;
};

int main()
{
    // 7 percent tax on a C++ book: type is Taxed<CppBook>, deduced by CTAD.
    Taxed item1{0.07, CppBook{"Effective C++", Money{19.0}}};
    std::cout << "Book with 7% tax:        " << show(item1.price()) << '\n';

    // 20 percent discount then 19 percent tax on a ticket. The whole composition
    // is one value of type Taxed<Discounted<ConferenceTicket>>; no heap at all.
    Taxed item2{0.19, Discounted{0.2, ConferenceTicket{"CppCon", Money{999.0}}}};
    std::cout << "Ticket discounted+taxed: " << show(item2.price()) << '\n';

    std::cout << "\nThe composition is a single stack-allocated value; price()\n"
                 "inlines through every layer with no virtual call and no pointer.\n";
    return 0;
}
