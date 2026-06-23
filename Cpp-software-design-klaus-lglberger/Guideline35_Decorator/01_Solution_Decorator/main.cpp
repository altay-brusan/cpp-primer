/*
 * Guideline 35 - Use Decorators to Add Customization Hierarchically
 *                (the classic GoF, reference-semantics Decorator)
 *
 * Concern: a merchandise team has many Items that all share one thing, a
 * price() tag, but the price must be modified in ever more ways (tax, then
 * discount, then combinations). Putting a taxRate_ data member in the Item base
 * was intrusive: every new modifier forced a change to Item and to every derived
 * class. Factoring the modifiers into their own inheritance hierarchy only made
 * it worse, exploding the type count and duplicating tax-and-discount code in a
 * combined DiscountAndTax class.
 *
 * The Decorator design pattern fixes this by COMPOSITION instead of inheritance.
 * Its GoF intent: "Attach additional responsibilities to an object dynamically.
 * Decorators provide a flexible alternative to subclassing for extending
 * functionality." A DecoratedItem both IS-an Item (it adheres to the Item
 * abstraction, Guideline 6) and HAS-an Item (it wraps another Item by
 * unique_ptr). Because the wrapped thing is itself just an Item, decorators
 * stack recursively: a Taxed can wrap a Discounted can wrap a ConferenceTicket.
 *
 * Key notes:
 *   - DecoratedItem is the extracted variation point (SRP). New modifiers are
 *     added without touching Item or the concrete items (OCP), and the recursive
 *     wrapper reuses one price() shape instead of duplicating combinations (DRY).
 *   - No null object is needed: an Item that wants no modifier is used as is.
 *   - Stacking order matters. Taxed-around-Discounted taxes the discounted price;
 *     Discounted-around-Taxed discounts the taxed price. Different results.
 *   - The price comes from reference semantics: many small allocations, nullptr
 *     checks, and one virtual call per layer of the wrapper.
 */
#include <cmath>
#include <format>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

// A tiny Money value type. operator-star scales a price by a factor; operator-plus
// adds two prices. Kept deliberately minimal for the demo.
struct Money
{
    double amount{};
};

Money operator*(Money m, double factor) { return Money{m.amount * factor}; }
Money operator+(Money lhs, Money rhs) { return Money{lhs.amount + rhs.amount}; }

std::string show(Money m) { return std::format("{:.2f}", m.amount); }

// The abstraction for every item: the only requirement is a price().
class Item
{
public:
    virtual ~Item() = default;
    virtual Money price() const = 0;
};

// The extracted variation point. It IS-an Item and HAS-an Item, so it forms the
// base for any wrapping modifier. Still abstract: price() is left undefined.
class DecoratedItem : public Item
{
public:
    explicit DecoratedItem(std::unique_ptr<Item> item) : m_item(std::move(item))
    {
        if (!m_item)
            throw std::invalid_argument("Invalid item");
    }

protected:
    Item& item() { return *m_item; }
    const Item& item() const { return *m_item; }

private:
    std::unique_ptr<Item> m_item;
};

// Concrete leaf items. Each is oblivious to tax or discount.
class CppBook : public Item
{
public:
    CppBook(std::string title, Money price) : m_title(std::move(title)), m_price(price) {}

    const std::string& title() const { return m_title; }
    Money price() const override { return m_price; }

private:
    std::string m_title;
    Money m_price;
};

class ConferenceTicket : public Item
{
public:
    ConferenceTicket(std::string name, Money price) : m_name(std::move(name)), m_price(price) {}

    const std::string& name() const { return m_name; }
    Money price() const override { return m_price; }

private:
    std::string m_name;
    Money m_price;
};

// Two stackable modifiers. Each wraps an Item and adapts its price().
class Discounted : public DecoratedItem
{
public:
    Discounted(double discount, std::unique_ptr<Item> item)
        : DecoratedItem(std::move(item)), m_factor(1.0 - discount)
    {
        if (!std::isfinite(discount) || discount < 0.0 || discount > 1.0)
            throw std::invalid_argument("Invalid discount");
    }

    Money price() const override { return item().price() * m_factor; }

private:
    double m_factor;
};

class Taxed : public DecoratedItem
{
public:
    Taxed(double taxRate, std::unique_ptr<Item> item)
        : DecoratedItem(std::move(item)), m_factor(1.0 + taxRate)
    {
        if (!std::isfinite(taxRate) || taxRate < 0.0)
            throw std::invalid_argument("Invalid tax");
    }

    Money price() const override { return item().price() * m_factor; }

private:
    double m_factor;
};

int main()
{
    // A C++ book with 7 percent tax: 19.00 times 1.07 equals 20.33.
    auto book = std::make_unique<CppBook>("Effective C++", Money{19.0});
    std::cout << "Book base price:        " << show(book->price()) << '\n';
    std::unique_ptr<Item> item1 = std::make_unique<Taxed>(0.07, std::move(book));
    std::cout << "Book with 7% tax:       " << show(item1->price()) << '\n';

    // A conference ticket with a 20 percent early-bird discount and 19 percent
    // tax: (999.00 times 0.80) times 1.19 equals 951.05.
    std::unique_ptr<Item> item2 =
        std::make_unique<Taxed>(0.19,
            std::make_unique<Discounted>(0.2,
                std::make_unique<ConferenceTicket>("CppCon", Money{999.0})));
    std::cout << "Ticket discounted+taxed: " << show(item2->price()) << '\n';

    // Same parts, swapped order: discount the already-taxed ticket. With pure
    // multiplicative factors the two orders happen to coincide (951.05), but in
    // general the order is significant, e.g. a fixed shipping fee added before
    // versus after a percentage tax would differ.
    std::unique_ptr<Item> item3 =
        std::make_unique<Discounted>(0.2,
            std::make_unique<Taxed>(0.19,
                std::make_unique<ConferenceTicket>("CppCon", Money{999.0})));
    std::cout << "Ticket taxed+discounted: " << show(item3->price()) << '\n';

    std::cout << "\nEach modifier was added by wrapping, never by editing Item or\n"
                 "the concrete items. Decorators stack recursively through price().\n";
    return 0;
}
