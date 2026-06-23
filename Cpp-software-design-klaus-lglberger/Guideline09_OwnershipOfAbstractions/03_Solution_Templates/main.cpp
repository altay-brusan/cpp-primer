/*
 * Guideline 9 - Pay Attention to the Ownership of Abstractions (DIP via
 * templates and concepts, where ownership is automatic)
 *
 * The book stresses that the DIP is not only about base classes. Dependency
 * inversion is also achieved with templates, and in that context the question of
 * ownership resolves itself. A high-level algorithm states its requirements as a
 * concept; calling code (the low level) must satisfy that concept. Because the
 * concept is written together with the algorithm in the high level, the high
 * level OWNS the requirements automatically, and every concrete type depends on
 * them. This mirrors std::copy_if owning InputIt, OutputIt, and UnaryPredicate.
 *
 * Key notes:
 *   - The PluginLike concept is the abstraction. It is defined right here, with
 *     the high-level runEditor algorithm, so ownership lives in the high level
 *     by construction; there is no header to move around.
 *   - VimMode and Loud are low-level value types. They contain no base class and
 *     no virtual functions, yet they depend on the high-level requirements: they
 *     must provide name() and apply(). The dependency runs low to high.
 *   - This is the same inversion as the inheritance solution, achieved with a
 *     different abstraction mechanism. Any abstraction that the high level owns
 *     can invert dependencies: base classes, concepts, or overload sets.
 */
#include <concepts>
#include <iostream>
#include <string>
#include <utility>

// The abstraction, OWNED BY THE HIGH LEVEL. The requirements on a plug-in are
// expressed as a concept and live next to the algorithm that consumes them.
template <typename P>
concept PluginLike = requires(const P plugin, std::string text) {
    { plugin.name() } -> std::convertible_to<std::string>;
    { plugin.apply(text) } -> std::convertible_to<std::string>;
};

// The high-level algorithm. It depends only on the concept it owns, not on any
// concrete plug-in type.
template <PluginLike P>
std::string runEditor(const P& plugin, std::string text)
{
    std::cout << "  plug-in: " << plugin.name() << '\n';
    return plugin.apply(std::move(text));
}

// Low-level value types. No base class, no virtual functions; they simply
// satisfy the high-level requirements.
struct VimMode
{
    std::string name() const { return "VimMode"; }
    std::string apply(std::string text) const { return "[vim] " + text; }
};

struct Loud
{
    std::string name() const { return "Loud"; }
    std::string apply(std::string text) const { return text + "!!!"; }
};

int main()
{
    std::cout << "Dependency inversion via a high-level-owned concept:\n";
    std::cout << "  output: " << runEditor(VimMode{}, "hello world") << '\n';
    std::cout << "  output: " << runEditor(Loud{}, "hello world") << '\n';

    std::cout << "\nThe PluginLike concept is owned by the high-level algorithm.\n"
                 "VimMode and Loud are low-level value types that depend on those\n"
                 "requirements. Ownership is automatic, so the DIP holds with no\n"
                 "base class at all, just like std::copy_if and its concepts.\n";
    return 0;
}
