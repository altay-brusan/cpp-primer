/*
 * Guideline 2 - Don't Repeat Yourself: a single source of truth for the tax rate (REFINEMENT)
 *
 * This file demonstrates the second changeability aspect from the book: the Don't Repeat
 * Yourself (DRY) principle, illustrated with the Item hierarchy. In the book's first version
 * every item (CppBook, ConferenceTicket, and many more) hardcodes "price * 1.15" in its own
 * constructor, so the 15 percent tax rate is duplicated across the whole codebase. When the
 * rate changes - as it really did in Germany in 2021 - the edit must be repeated in every
 * single derived class, which is error-prone and easy to get inconsistent. This sample keeps
 * the tax rate in exactly one place so the change happens once, and explains in comments what
 * the duplicated version looked like and why it hurt.
 *
 * Key notes:
 *   - SRP separates reasons to change; DRY makes sure each piece of knowledge lives in ONE place.
 *     The two principles usually reinforce each other.
 *   - taxRate() is the single source of truth. Every item routes through applyTax(), so changing
 *     0.15 to 0.16 is a one-line, one-place edit instead of a codebase-wide sweep.
 *   - The book notes the full, scalable solution (per-item, configurable tax) uses the Decorator
 *     pattern in Guideline 35; here we only establish the DRY foundation.
 *   - This is also a reminder of YAGNI: do not over-separate before you know what change to expect.
 */

#include <iostream>
#include <memory>
#include <numeric>
#include <string>
#include <vector>

// A minimal stand-in for the book's Money type (standard library only).
struct Money
{
    double amount{ 0.0 };
};

Money operator*(Money m, double factor) { return Money{ m.amount * factor }; }
Money operator+(Money lhs, Money rhs) { return Money{ lhs.amount + rhs.amount }; }

// --------------------------------------------------------------------------------------
// THE single source of truth for taxation. In the DRY-violating version this 0.15 was
// copy-pasted into every constructor as "price * 1.15". Here it exists exactly once, so a
// rate change is a one-place edit.
//
// Duplicated (problematic) version, for reference - do NOT do this in many classes:
//     priceWithTax_ = price * 1.15;  // repeated in CppBook, ConferenceTicket, ...
// --------------------------------------------------------------------------------------
double taxRate() { return 0.15; }                 // change once, applies everywhere
Money applyTax(Money price) { return price * (1.0 + taxRate()); }

class Item
{
public:
    virtual ~Item() = default;
    virtual Money price() const = 0;
};

class CppBook : public Item
{
public:
    CppBook(std::string title, std::string author, Money price)
        : m_title{ std::move(title) }
        , m_author{ std::move(author) }
        , m_priceWithTax{ applyTax(price) } // routes through the single source of truth
    {}

    const std::string& title() const { return m_title; }
    const std::string& author() const { return m_author; }
    Money price() const override { return m_priceWithTax; }

private:
    std::string m_title;
    std::string m_author;
    Money m_priceWithTax;
};

class ConferenceTicket : public Item
{
public:
    ConferenceTicket(std::string name, Money price)
        : m_name{ std::move(name) }
        , m_priceWithTax{ applyTax(price) } // same single source of truth, no duplicated 1.15
    {}

    const std::string& name() const { return m_name; }
    Money price() const override { return m_priceWithTax; }

private:
    std::string m_name;
    Money m_priceWithTax;
};

int main()
{
    std::vector<std::unique_ptr<Item>> items;
    items.push_back(std::make_unique<CppBook>("Effective C++", "Scott Meyers", Money{ 19.99 }));
    items.push_back(std::make_unique<CppBook>("C++ Templates", "Vandevoorde et al.", Money{ 49.99 }));
    items.push_back(std::make_unique<ConferenceTicket>("CppCon", Money{ 999.0 }));
    items.push_back(std::make_unique<ConferenceTicket>("Meeting C++", Money{ 699.0 }));
    items.push_back(std::make_unique<ConferenceTicket>("C++ on Sea", Money{ 499.0 }));

    const Money total = std::accumulate(
        begin(items), end(items), Money{},
        [](Money accu, const auto& item) { return accu + item->price(); });

    std::cout << "DRY: the " << (taxRate() * 100.0) << "% tax rate lives in one place\n";
    std::cout << "  total price (incl. tax): " << total.amount << '\n';
    std::cout << "\nIf the rate changes to 16%, edit taxRate() once - not every Item class.\n";
    return 0;
}
