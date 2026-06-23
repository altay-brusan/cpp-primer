/*
 * Guideline 36 - Understand the Trade-off Between Runtime and Compile Time Abstraction
 *                (the RUNTIME, value-based Decorator built with Type Erasure)
 *
 * Guideline 35 showed the Decorator pattern, but only in a classic, pointer to
 * base, object-oriented form. Guideline 36 revisits Decorator twice to weigh the
 * two ends of the design space. This file is the RUNTIME end: a value-based
 * Decorator whose decorations are chosen, composed, and even decided WHILE THE
 * PROGRAM RUNS. The price for that flexibility is one virtual indirection plus a
 * heap allocation per layer.
 *
 * The enabling technique is Type Erasure (Guideline 32). A single value type
 * Item wraps any priced thing behind a hidden Concept and Model hierarchy, so
 * many different decorations share one static type and can live together in one
 * container. Discounted and Taxed are plain value types that simply OWN an Item
 * and forward price() to it, which is exactly the Decorator relationship without
 * a single visible pointer in user code.
 *
 * Key notes:
 *   - Runtime abstraction: the decoration stack is data, so it can be built from
 *     user input, a config flag, or a computed result, all at run time.
 *   - One static type Item erases every decoration, so a vector of Item can hold
 *     wildly different stacks side by side. That is the runtime flexibility win.
 *   - Cost: each layer adds a heap allocation plus a virtual call through pimpl,
 *     so the optimizer cannot inline across layers the way the templates can.
 *   - Value semantics (Guideline 22): Item is copyable via clone and needs no
 *     manual new or delete in user code, unlike the classic Decorator.
 *   - Strength beyond speed: implementation details hide behind Item, so changes
 *     stay local and recompilation stays cheap.
 */
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

// A tiny value type standing in for the book Money type.
struct Money
{
    double amount{};
};

Money operator*(Money m, double factor) { return Money{m.amount * factor}; }
Money operator+(Money a, Money b) { return Money{a.amount + b.amount}; }
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

// The Type Erasure wrapper. Any copyable type that offers price() becomes an
// Item, with no inheritance required from the wrapped type.
class Item
{
public:
    template <typename T>
    Item(T item) : m_pimpl(std::make_unique<Model<T>>(std::move(item)))
    {
    }

    Item(const Item& other) : m_pimpl(other.m_pimpl->clone()) {}
    Item& operator=(const Item& other)
    {
        m_pimpl = other.m_pimpl->clone();
        return *this;
    }
    Item(Item&&) noexcept = default;
    Item& operator=(Item&&) noexcept = default;
    ~Item() = default;

    Money price() const { return m_pimpl->price(); }

private:
    // The erased interface: the set of requirements for any wrapped item.
    struct Concept
    {
        virtual ~Concept() = default;
        virtual Money price() const = 0;
        virtual std::unique_ptr<Concept> clone() const = 0;
    };

    // The adapter that holds a concrete T and forwards the requirements to it.
    template <typename T>
    struct Model : Concept
    {
        explicit Model(T item) : m_item(std::move(item)) {}
        Money price() const override { return m_item.price(); }
        std::unique_ptr<Concept> clone() const override
        {
            return std::make_unique<Model>(*this);
        }
        T m_item;
    };

    std::unique_ptr<Concept> m_pimpl;
};

// Value-based Decorators: they OWN an Item and forward price() to it. Note that
// neither derives from any base, yet both are perfect Decorators.
class Discounted
{
public:
    Discounted(double discount, Item item)
        : m_item(std::move(item)), m_factor(1.0 - discount)
    {
    }
    Money price() const { return m_item.price() * m_factor; }

private:
    Item m_item;
    double m_factor;
};

class Taxed
{
public:
    Taxed(double taxRate, Item item)
        : m_item(std::move(item)), m_factor(1.0 + taxRate)
    {
    }
    Money price() const { return m_item.price() * m_factor; }

private:
    Item m_item;
    double m_factor;
};

int main()
{
    // 20% discount, then 15% tax: (499 * 0.8) * 1.15 = 459.08
    Item item(Taxed(0.15, Discounted(0.2, ConferenceTicket{"Core C++", Money{499.0}})));
    std::cout << "One composed stack, price = " << item.price() << '\n';

    // Runtime flexibility 1: many different decoration stacks share one type and
    // live together in a single container.
    std::vector<Item> cart;
    cart.emplace_back(ConferenceTicket{"Plain", Money{100.0}});
    cart.emplace_back(Discounted(0.10, ConferenceTicket{"Member", Money{100.0}}));
    cart.emplace_back(Taxed(0.19, Discounted(0.10, ConferenceTicket{"Full", Money{100.0}})));

    Money total{};
    for (const Item& it : cart)
        total = total + it.price();
    std::cout << "Cart of " << cart.size() << " mixed stacks, total = " << total << '\n';

    // Runtime flexibility 2: decide WHILE RUNNING whether to add another layer.
    bool applyTax = (cart.size() > 2); // pretend this came from user input
    Item base(ConferenceTicket{"Late", Money{200.0}});
    Item finalItem = applyTax ? Item(Taxed(0.19, base)) : base;
    std::cout << "Layer chosen at run time, price = " << finalItem.price() << '\n';

    std::cout << "\nThe decoration stack is data: composed, stored, and decided\n"
                 "at run time. The cost is one heap allocation plus one virtual\n"
                 "call per layer, traded for maximum runtime flexibility.\n";
    return 0;
}
