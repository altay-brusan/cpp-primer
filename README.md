# cpp-primer
Curated C++ best practices, modern patterns, and commonly overlooked features — designed to prime AI agents before they write your code.

## Best Practices
- Prefer RAII and deterministic cleanup over manual `new`/`delete`.
- Use `const` correctness and references to communicate intent clearly.
- Favor standard library containers/algorithms over handwritten low-level loops.
- Avoid undefined behavior; initialize values and respect object lifetimes.
- Keep interfaces small, explicit, and exception-safe.

## Modern Patterns
- Prefer smart pointers (`std::unique_ptr`, `std::shared_ptr`) only for ownership.
- Use move semantics (`std::move`) when transferring ownership.
- Use `std::optional`, `std::variant`, and `std::expected`-style error/value modeling patterns.
- Prefer range-based loops and C++20 ranges where readable.
- Use `constexpr` and `consteval` for compile-time guarantees when appropriate.

## Commonly Overlooked Features
- `[[nodiscard]]` to prevent ignored important return values.
- `std::string_view` for non-owning string parameters.
- `std::span` for safe, non-owning contiguous views.
- Structured bindings and designated initializers for clarity.
- Three-way comparison (`<=>`) and defaulted comparisons.
- Concepts to constrain templates with meaningful diagnostics.

## AI Agent Priming Checklist
Before generating code, ensure the agent:
1. Uses modern C++ idioms first, not C-style patterns.
2. Chooses ownership models explicitly.
3. Prefers standard-library abstractions to custom utilities.
4. Preserves exception and lifetime safety.
5. Produces minimal, readable, maintainable code.
