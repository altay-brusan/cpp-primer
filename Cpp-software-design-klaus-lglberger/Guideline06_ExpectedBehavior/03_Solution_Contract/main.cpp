/*
 * Guideline 6 - Adhere to the Expected Behavior of Abstractions (honoring the contract)
 *
 * The Rectangle and Square case is one instance of a general rule: an abstraction
 * is a contract, and every subtype must honor it. The book spells out the
 * behavioral subtyping requirements of the Liskov Substitution Principle. This
 * sample shows a hierarchy that GETS THEM RIGHT, so substitution is always safe:
 *
 *   - Preconditions cannot be strengthened in a subtype: a subtype may not demand
 *     more of its inputs than the base promised to accept.
 *   - Postconditions cannot be weakened in a subtype: a subtype may not deliver
 *     less in its result than the base promised to return.
 *   - Invariants of the base must be preserved by the subtype.
 *
 * The abstraction here is a Discount calculator. Its contract: accept any price
 * that is zero or greater (the precondition), and return a discounted price that
 * is itself zero or greater and never above the input (the postcondition). The
 * derived LoyaltyDiscount honors that exact contract - it accepts every price the
 * base accepts and keeps the same guarantees - so calling code that depends only
 * on the abstraction can use any Discount interchangeably.
 *
 * Key notes:
 *   - apply() of the base accepts every price that is zero or greater. The
 *     derived type accepts the same range; it does NOT strengthen the
 *     precondition, so no input that worked before is rejected now.
 *   - Both types guarantee a result that is zero or greater and not above the
 *     input. The derived type does NOT weaken that postcondition.
 *   - checkout() depends only on the Discount abstraction. Because every subtype
 *     honors the contract, checkout() behaves correctly for all of them - this is
 *     a genuine IS-A relationship, the opposite of the Rectangle and Square case.
 *   - A WRONG subtype would, for example, reject prices below 100 (strengthening
 *     the precondition) or return a price above the input (weakening the
 *     postcondition). Both are described here in prose only, never in live code,
 *     because either one is an LSP violation.
 *   - This file is an AFTER picture: a hierarchy where the contract is honored.
 */
#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

// The abstraction is a contract.
//   Precondition  : price is zero or greater.
//   Postcondition : the result is zero or greater and not above 'price'.
class Discount
{
public:
    virtual ~Discount() = default;
    virtual const char* name() const = 0;
    virtual double apply(double price) const = 0;
};

// Honors the contract: accepts any non-negative price, returns a percentage off,
// clamped so the result stays within the promised range.
class PercentageDiscount : public Discount
{
public:
    explicit PercentageDiscount(double percent) : m_percent{ percent } {}

    const char* name() const override { return "PercentageDiscount"; }

    double apply(double price) const override
    {
        const double off = price * (m_percent / 100.0);
        const double result = price - off;
        return std::clamp(result, 0.0, price); // keep the postcondition
    }

private:
    double m_percent{ 0.0 };
};

// Also honors the EXACT same contract. It does not require a larger minimum
// price (no strengthened precondition) and never returns more than the input
// (no weakened postcondition). It simply does more work internally.
class LoyaltyDiscount : public Discount
{
public:
    LoyaltyDiscount(double percent, double bonus) : m_percent{ percent }, m_bonus{ bonus } {}

    const char* name() const override { return "LoyaltyDiscount"; }

    double apply(double price) const override
    {
        const double off = price * (m_percent / 100.0) + m_bonus;
        const double result = price - off;
        return std::clamp(result, 0.0, price); // same guarantees as the base
    }

private:
    double m_percent{ 0.0 };
    double m_bonus{ 0.0 };
};

// Calling code depends ONLY on the Discount abstraction. Because every subtype
// honors the contract, this function is correct for all of them, including ones
// written later.
double checkout(const Discount& discount, double price)
{
    const double final = discount.apply(price);
    const bool inRange = (final >= 0.0) && (final <= price); // the promised range
    std::cout << "  " << discount.name() << ": price=" << price
              << " -> final=" << final
              << " (postcondition " << (inRange ? "HONORED" : "BROKEN") << ")\n";
    return final;
}

int main()
{
    std::cout << "Honored contract (every Discount keeps the same promises):\n";

    std::vector<std::unique_ptr<Discount>> discounts;
    discounts.push_back(std::make_unique<PercentageDiscount>(10.0));
    discounts.push_back(std::make_unique<LoyaltyDiscount>(10.0, 5.0));

    for (const auto& d : discounts)
    {
        // The same inputs the base accepts (zero or greater) work for every
        // subtype, because none of them strengthens the precondition.
        checkout(*d, 0.0);
        checkout(*d, 80.0);
    }

    std::cout << "\nBoth subtypes accept every price the abstraction accepts and\n"
                 "keep every result within the promised range. A subtype that\n"
                 "rejected small prices (a strengthened precondition) or returned\n"
                 "more than the input (a weakened postcondition) would violate the\n"
                 "LSP. Honoring the contract is what makes this a true IS-A.\n";
    return 0;
}
