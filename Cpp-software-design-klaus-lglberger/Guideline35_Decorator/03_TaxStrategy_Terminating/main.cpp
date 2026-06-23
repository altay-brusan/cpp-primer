/*
 * Guideline 35 - Use Decorators to Add Customization Hierarchically
 *                (taming the flexibility: a terminating Decorator plus Strategy)
 *
 * Concern: the great strength of Decorator, that any wrapper composes with any
 * other, is also a danger. Nothing stops a Taxed wrapping another Taxed, or a
 * Discounted applied to an already-taxed item. Both would make the government
 * happy but are nonsensical and should be impossible by design. The book quotes
 * Scott Meyers: make interfaces easy to use correctly and hard to use
 * incorrectly. Since tax is, in reality, a complex topic that deserves its own
 * varying logic, the book separates it out with the Strategy design pattern.
 *
 * TaxStrategy isolates HOW a tax is computed (Guideline 19). TaxedItem combines
 * an Item with a TaxStrategy, but, crucially, TaxedItem is NOT itself an Item.
 * It cannot be wrapped by another decorator, so it acts as a TERMINATING
 * decorator: it can only ever be the last step. That single design choice rules
 * out double taxation and discount-after-tax mistakes at compile time. Instead
 * of price(), TaxedItem exposes netPrice() (before tax) and grossPrice() (after
 * tax), making the distinction explicit at the call site.
 *
 * Key notes:
 *   - Ordinary modifiers (Discounted) stay reference-semantics decorators and
 *     still stack freely; only tax is special and handled apart.
 *   - TaxedItem is the terminating decorator: not an Item, so it ends the chain
 *     and cannot be re-wrapped, which forbids nonsensical compositions by design.
 *   - TaxStrategy is injected, so different jurisdictions are different strategies
 *     with no change to TaxedItem: Strategy and Decorator combined.
 *   - netPrice versus grossPrice names the tax boundary instead of hiding it in a
 *     plain price().
 */
#include <cmath>
#include <format>
#include <iostream>
#include <memory>
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

// The Item abstraction and a stackable, non-tax modifier (Discounted) as before.
class Item
{
public:
    virtual ~Item() = default;
    virtual Money price() const = 0;
};

class DecoratedItem : public Item
{
public:
    explicit DecoratedItem(std::unique_ptr<Item> item) : m_item(std::move(item))
    {
        if (!m_item)
            throw std::invalid_argument("Invalid item");
    }

protected:
    const Item& item() const { return *m_item; }

private:
    std::unique_ptr<Item> m_item;
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

// Tax is special: isolate HOW it is computed behind a Strategy.
class TaxStrategy
{
public:
    virtual ~TaxStrategy() = default;
    virtual Money applyTax(Money price) const = 0;
};

class FlatTax : public TaxStrategy
{
public:
    explicit FlatTax(double rate) : m_factor(1.0 + rate)
    {
        if (!std::isfinite(rate) || rate < 0.0)
            throw std::invalid_argument("Invalid tax");
    }

    Money applyTax(Money price) const override { return price * m_factor; }

private:
    double m_factor;
};

// The terminating decorator: it wraps an Item plus a TaxStrategy, but is NOT an
// Item itself, so it can only be the final step and never be re-wrapped.
class TaxedItem
{
public:
    TaxedItem(std::unique_ptr<Item> item, std::unique_ptr<TaxStrategy> taxer)
        : m_item(std::move(item)), m_taxer(std::move(taxer))
    {
        if (!m_item || !m_taxer)
            throw std::invalid_argument("Invalid taxed item");
    }

    Money netPrice() const { return m_item->price(); }
    Money grossPrice() const { return m_taxer->applyTax(m_item->price()); }

private:
    std::unique_ptr<Item> m_item;
    std::unique_ptr<TaxStrategy> m_taxer;
};

int main()
{
    // Build the discountable part with ordinary decorators, then terminate the
    // chain exactly once with TaxedItem. Tax can no longer be applied twice.
    TaxedItem ticket{
        std::make_unique<Discounted>(0.2,
            std::make_unique<ConferenceTicket>("CppCon", Money{999.0})),
        std::make_unique<FlatTax>(0.19)};

    std::cout << "Net price (before tax):  " << show(ticket.netPrice()) << '\n';
    std::cout << "Gross price (with tax):  " << show(ticket.grossPrice()) << '\n';

    std::cout << "\nTaxedItem is not an Item, so it ends the decorator chain: you\n"
                 "cannot tax twice or discount a taxed price. Hard to use wrongly.\n";
    return 0;
}
