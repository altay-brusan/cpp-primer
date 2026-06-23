# Guideline 35 — Use Decorators to Add Customization Hierarchically

> **Concern:** an item needs its `price()` modified in ever more ways — tax, then
> discount, then arbitrary combinations. Baking the modifiers into the base class
> (a `taxRate_` member) is **intrusive**: every new modifier changes `Item` and
> all its children. Factoring them into an inheritance hierarchy is worse — the
> type count explodes and a combined `DiscountAndTax` duplicates code. The
> **Decorator** design pattern attaches responsibilities by **wrapping**: a
> wrapper that both *is* an `Item` and *has* an `Item` adds behavior in `price()`
> and forwards the rest, so modifiers **stack hierarchically** and are added
> **without modifying existing code**.

## The idea

The book follows two merchandise developers whose `Item` hierarchy (a `CppBook`,
a `ConferenceTicket`, …) keeps needing new price modifiers. After rejecting a
base-class data member and a modifier inheritance tree, they reach Strategy — but
Strategy isolates *how one thing* is done and does not let independent modifiers
**combine and reuse** each other gracefully. What they actually need is a
*hierarchical* form: the **Decorator** pattern.

The GoF intent: *"Attach additional responsibilities to an object dynamically.
Decorators provide a flexible alternative to subclassing for extending
functionality."* The key class is `DecoratedItem`: it derives from `Item` (so it
honors the abstraction, Guideline 6) **and** holds an `Item` (composition). Since
the wrapped thing is itself just an `Item`, decorators nest recursively —
`Taxed` around `Discounted` around `ConferenceTicket` — and `price()` is where
the chain is evaluated.

This separation gives the SOLID payoff the book highlights: the extracted
`DecoratedItem` is the variation point (**SRP**); new modifiers plug in without
editing `Item` or the concrete items (**OCP**); the recursive wrapper reuses one
`price()` shape instead of duplicating combinations (**DRY**); and an item that
wants no modifier is used as is — **no null object** required.

## Samples

| # | Sample | What it shows |
|---|--------|---------------|
| 01 | `01_Solution_Decorator` | The classic GoF, reference-semantics Decorator. `Item`, leaf `CppBook`/`ConferenceTicket`, an abstract `DecoratedItem` base, and `Taxed`/`Discounted` wrappers built with `unique_ptr`. `main()` stacks them and prints the composed prices; swapping the stacking order shows order is significant. |
| 02 | `02_ValueDecorator` | A **value-based, compile-time** Decorator: `Taxed<Item>`/`Discounted<Item>` hold the wrapped item *by value*, constrained by a `PricedItem` concept. `Taxed<Discounted<ConferenceTicket>>` is one stack value — no base class, no heap, no virtual call — the book's "ace up the sleeve." |
| 03 | `03_TaxStrategy_Terminating` | Taming the flexibility. Tax is separated into a `TaxStrategy` (Strategy, Guideline 19) combined in a `TaxedItem` that is **not** an `Item` — a *terminating* decorator that can only be the last step, forbidding double taxation by design. Exposes `netPrice()`/`grossPrice()`. |

Each sample's `main()` composes several decorators and prints the result; every
file is a single self-contained `main.cpp` using the standard library only.

## Build & run

```powershell
# Interactive menu for this guideline:
./run.ps1 -Guideline 35

# Verify every sample compiles (MSVC, /std:c++latest):
./run.ps1 -Verify -Guideline 35
```

## Notes

- **Stacking order matters.** `Taxed`-around-`Discounted` taxes the discounted
  price; `Discounted`-around-`Taxed` discounts the taxed price. With pure
  multiplicative factors the two happen to coincide, but a non-multiplicative
  modifier (a flat shipping fee, a cap) makes the order observable. Choose it
  deliberately — and, as sample 03 shows, design out the combinations that make
  no sense (Meyers: *make interfaces easy to use correctly and hard to use
  incorrectly*).
- **Decorator vs. Strategy.** Both customize functionality, but at opposite ends.
  **Strategy** removes the dependency on *how one operation is implemented* and
  lets you **switch** implementations — it is the "guts" of a behavior.
  **Decorator** removes the dependency between *attachable pieces* and lets you
  **combine and augment** behavior — it is the "skin." Strategy *replaces*;
  Decorator *adds*. They compose well (sample 03 uses both).
- **Decorator vs. Adapter.** Despite the similar-sounding names they are barely
  related: Adapter *changes* an interface to an expected one (Guideline 24);
  Decorator *preserves* the interface and only adds responsibilities.
- **Shortcomings.** Every layer is one level of indirection — in the OO form, one
  virtual call per decorator — so heavy stacking has a cost; benchmark before
  worrying. The reference-semantics form also brings pointers, nullptr checks,
  dangling risk, and many small allocations. Sample 02's value-based form removes
  the indirection and the heap at the cost of runtime swapping and a distinct
  type per composition. *It depends.*

## Related

→ Guideline 19 (Strategy) is the pattern Decorator is most often confused with,
and is reused in sample 03. → Guideline 24 (Adapter) is the other look-alike.
→ Guideline 20 (Composition over Inheritance) is the principle Decorator
embodies. → Guideline 22/23 (Value Semantics) motivate sample 02's value-based
variant.
```
