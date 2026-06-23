/*
 * Guideline 17 - Consider std::variant for Implementing Visitor (value-based)
 *
 * This is the modern, VALUE-BASED Visitor from the book. Instead of the
 * intrusive Gang-of-Four Visitor (a Shape base class, an accept hook, a Visitor
 * base class, virtual visit functions, and owning pointers), we model the
 * closed set of shapes as a single sum type:
 *
 *     using Shape = std::variant<Circle, Square>;
 *
 * The shapes are plain value types: no base class, no virtual functions, no
 * accept member. The std::variant takes over the job the base class used to do,
 * and because variants are values we can store them DIRECTLY in a std::vector
 * with no smart pointers and no manual allocation. An operation is just a
 * callable that supplies one operator() per alternative; std::visit performs the
 * type dispatch for us. Adding a new operation is a brand-new visitor that
 * touches no existing code, so the design stays open for operations (the OCP),
 * exactly like the classic Visitor but with far less machinery.
 *
 * Key notes:
 *   - Value semantics: Circle and Square are stored by value inside the variant,
 *     and the variants are stored by value inside the vector. No new, no delete,
 *     no pointers, no leaks to reason about.
 *   - Nonintrusive: the shapes know nothing about visiting. There is no accept
 *     member and no Visitor base class, so this style can be bolted onto types
 *     you do not own.
 *   - Two visitor styles are shown: Draw is a hand-written struct with one
 *     operator() per alternative (the book Print or Draw style); area uses the
 *     overload helper to fuse a set of lambdas into one callable on the fly.
 *   - Loose coupling: the only contract is "one operator() per alternative."
 *     Return types are chosen per operation (void for Draw, double for area),
 *     not dictated by a base class.
 *   - Closed type set: adding a Pentagon means editing the Shape alias AND every
 *     visitor. The compiler flags a missing operator(), so the omission is a
 *     COMPILE error, never a silent fall-through. That cost is shown in comments.
 */
#include <iostream>
#include <numbers>
#include <string>
#include <variant>
#include <vector>

// A shared, tiny value type. The center is carried by value, no allocation.
struct Point
{
    double x{0.0};
    double y{0.0};
};

// Plain geometric primitives: no Shape base class, no virtual functions, no
// accept member. They are exactly what they are, nothing more.
struct Circle
{
    double radius{0.0};
    Point center{};
};

struct Square
{
    double side{0.0};
    Point center{};
};

// The closed set of TYPES. std::variant replaces the old Shape base class as
// the abstraction over "some shape." To add a Pentagon you would write:
//     using Shape = std::variant<Circle, Square, Pentagon>;
// and then extend every visitor below.
using Shape = std::variant<Circle, Square>;

// A vector of shapes needs no pointers now: variants are values.
using Shapes = std::vector<Shape>;

// The classic overload helper: it inherits the call operators of every lambda
// passed to it and merges them into one callable. The deduction guide lets us
// write overload{ lambda1, lambda2, ... } without spelling out the types. This
// compiles on MSVC with C++20 and later.
template <class... Ts>
struct overload : Ts...
{
    using Ts::operator()...;
};
template <class... Ts>
overload(Ts...) -> overload<Ts...>;

// OPERATION 1 (struct visitor style): one operator() per alternative, the same
// shape the book uses for Print and Draw. No base class, no virtual functions.
struct Draw
{
    void operator()(const Circle& c) const
    {
        std::cout << "Circle(r=" << c.radius
                  << ") at (" << c.center.x << ", " << c.center.y << ")\n";
    }
    void operator()(const Square& s) const
    {
        std::cout << "Square(s=" << s.side
                  << ") at (" << s.center.x << ", " << s.center.y << ")\n";
    }
    // A Pentagon alternative would need its own operator() HERE, or the call to
    // std::visit below would fail to compile.
};

// OPERATION 2 (overload lambda style): area is a SECOND, independent visitor.
// Adding it touched no existing type and no existing visitor. This is the open
// axis of the design: new operations are free.
double area(const Shape& shape)
{
    return std::visit(
        overload{
            [](const Circle& c) { return std::numbers::pi * c.radius * c.radius; },
            [](const Square& s) { return s.side * s.side; },
        },
        shape);
}

int main()
{
    // Thanks to the nonexplicit variant constructor, a Circle or Square converts
    // implicitly into a Shape, so we add the values directly.
    Shapes shapes{
        Circle{2.3, {1.0, 1.0}},
        Square{1.2, {2.0, 0.0}},
        Circle{4.1, {0.0, 3.0}},
    };

    std::cout << "Value-based Visitor (std::variant plus std::visit):\n";
    for (const auto& shape : shapes)
    {
        std::visit(Draw{}, shape);                 // operation 1
        std::cout << "  area = " << area(shape) << '\n'; // operation 2
    }

    std::cout << "\nNo base class, no virtual functions, no pointers.\n"
                 "Add an OPERATION  -> one new visitor, nothing else changes.\n"
                 "Add a TYPE        -> edit the Shape variant plus every visitor.\n";
    return 0;
}
