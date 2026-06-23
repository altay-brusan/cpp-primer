/*
 * Guideline 22 - Prefer Value Semantics over Reference Semantics
 *                (the value-semantics design: regular types, variant, optional)
 *
 * This is the AFTER picture. The same shapes problem and the same parse-an-int
 * problem, expressed with value semantics: regular value types, copies that are
 * deep and independent, std::variant instead of a pointer-to-base hierarchy,
 * and a result returned by value as a std::optional. The book's point is that
 * values are far easier to reason about: a copy copies the whole value, a const
 * value is const all the way down, a change is local and cannot surprise some
 * other part of the program, and there is no ownership, no nullptr, and no
 * lifetime bookkeeping. As a bonus the layout is contiguous, with no per-object
 * allocation and no virtual indirection.
 *
 * Key notes:
 *   - std::variant replaces the inheritance hierarchy: a closed set of value
 *     types in one container, dispatched with std::visit. No heap, no pointers.
 *   - Copying the container makes a deep, independent copy. Mutating the copy
 *     cannot affect the original: no aliasing, no shared mutable state.
 *   - const really means const: a const variant cannot be mutated through any
 *     path, unlike a const span over a vector.
 *   - Errors travel as a value via std::optional, returned by value. No output
 *     parameter, no nullptr, no allocation, no lifetime to manage.
 *   - No question of ownership or dangling: each value owns its own content and
 *     lives exactly as long as the variable that holds it.
 */
#include <charconv>
#include <iostream>
#include <optional>
#include <string_view>
#include <system_error>
#include <variant>
#include <vector>

constexpr double kPi = 3.141592653589793;

// Plain value types: no base class, no virtual functions, no pointers.
struct Circle
{
    double r{};
    double area() const { return kPi * r * r; }
    void describe() const { std::cout << "circle r=" << r << '\n'; }
};

struct Square
{
    double s{};
    double area() const { return s * s; }
    void describe() const { std::cout << "square s=" << s << '\n'; }
};

// A closed set of shapes held BY VALUE. This is the value-based replacement for
// a pointer-to-base hierarchy.
using ShapeV = std::variant<Circle, Square>;

double area(const ShapeV& sh)
{
    return std::visit([](const auto& x) { return x.area(); }, sh);
}

// Parse to an int and return the result by value. Present means success;
// empty means failure. No out-parameter, no nullptr, no allocation.
std::optional<int> toInt(std::string_view sv)
{
    int i{};
    const auto res = std::from_chars(sv.data(), sv.data() + sv.size(), i);
    if (res.ec == std::errc{})
        return i;
    return std::nullopt;
}

int main()
{
    // 1) Polymorphism without pointers: a vector of VALUES, visited in place.
    std::vector<ShapeV> shapes{Circle{2.0}, Square{3.0}};

    std::cout << "Shapes stored by value (contiguous, no heap per element):\n";
    for (const auto& sh : shapes)
        std::visit([](const auto& x) { x.describe(); }, sh);

    // 2) A copy is deep and independent. Mutating the copy cannot reach back
    //    and surprise the original: no aliasing.
    std::vector<ShapeV> copy = shapes;
    std::get<Circle>(copy[0]).r = 10.0;

    std::cout << "\nAfter writing radius=10 in the COPY only:\n";
    std::cout << "  original area: " << area(shapes[0]) << " (unchanged)\n";
    std::cout << "  copy area    : " << area(copy[0]) << '\n';

    // 3) const means const, all the way down.
    const std::vector<ShapeV> frozen = shapes;
    // std::get<Circle>(frozen[0]).r = 1.0; // would NOT compile: frozen is const
    std::cout << "  frozen area  : " << area(frozen[0]) << " (cannot be mutated)\n";

    // 4) Errors as a value, returned by value: no nullptr, no lifetime worries.
    std::cout << "\nParsing with a value result (std::optional):\n";
    for (std::string_view s : {std::string_view{"42"}, std::string_view{"oops"}})
    {
        if (const auto n = toInt(s))
            std::cout << "  \"" << s << "\" -> " << *n << '\n';
        else
            std::cout << "  \"" << s << "\" -> (not a number)\n";
    }

    std::cout << "\nValue semantics: copies are independent, const is total, and\n"
                 "there is no ownership, no nullptr, and no dangling to reason about.\n";
    return 0;
}
