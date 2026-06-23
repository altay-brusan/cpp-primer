/*
 * Guideline 15 - Design for the Addition of Types or Operations (procedural axis)
 *
 * This is the procedural / functional half of the expression problem. Instead
 * of a base class, the shapes are plain value types collected in a closed
 * std::variant. Operations are free visitors applied with std::visit. This is
 * the exact inversion of the object-oriented design in sample 01:
 *
 *   - Adding a new OPERATION is EASY. A serialize operation is one new visitor
 *     (a free function object) that handles each alternative. No existing type
 *     and no existing visitor is touched. This fulfills the Open-Closed
 *     Principle (OCP) with respect to operations.
 *
 *   - Adding a new TYPE is HARD. Introducing a Pentagon means editing the
 *     Shape variant alias AND every visitor, because each std::visit must
 *     handle every alternative or it fails to compile. The set of types is
 *     fixed by the variant, so the OCP is violated with respect to types.
 *
 * The book's takeaway: procedural and functional designs keep OPERATIONS open
 * and TYPES closed. Prefer this when you expect to add operations far more
 * often than types. (A bonus the book notes: with a closed variant a missing
 * case becomes a COMPILE error, not the silent fall-through of an enum switch.)
 *
 * Key notes:
 *   - The strength here is the open operation set: new verbs are added as
 *     standalone visitors, modifying nothing.
 *   - The weakness is the closed type set: a new alternative ripples into the
 *     variant and into every visitor that must now cover it.
 *   - The HARD direction (adding a Pentagon) is shown in comments only, so
 *     this file stays compilable while still making the cost explicit.
 */
#include <iostream>
#include <numbers>
#include <string>
#include <variant>
#include <vector>

// Plain value types. No base class, no virtual functions.
struct Circle { double radius; };
struct Square { double side; };
struct Triangle { double base; double height; };

// Closed set of TYPES. Adding a new shape means editing THIS alias (and then
// every visitor below). That is the painful axis of a procedural design.
//   To add a Pentagon you would change this to:
//     using Shape = std::variant<Circle, Square, Triangle, Pentagon>;
using Shape = std::variant<Circle, Square, Triangle>;

// Helper to build a visitor from a set of lambdas (the classic overload trick).
template <class... Ts>
struct overload : Ts...
{
    using Ts::operator()...;
};
template <class... Ts>
overload(Ts...) -> overload<Ts...>;

// OPERATION 1: draw. One visitor over the closed type set.
void draw(const Shape& shape)
{
    std::visit(overload{
                   [](const Circle& c) { std::cout << "Circle(r=" << c.radius << ")\n"; },
                   [](const Square& s) { std::cout << "Square(s=" << s.side << ")\n"; },
                   [](const Triangle& t) { std::cout << "Triangle(b=" << t.base << ", h=" << t.height << ")\n"; },
                   // A Pentagon alternative would have to be handled HERE too,
                   // or std::visit would fail to compile.
               },
               shape);
}

// OPERATION 2: area. A second, independent visitor.
double area(const Shape& shape)
{
    return std::visit(overload{
                          [](const Circle& c) { return std::numbers::pi * c.radius * c.radius; },
                          [](const Square& s) { return s.side * s.side; },
                          [](const Triangle& t) { return 0.5 * t.base * t.height; },
                      },
                      shape);
}

// OPERATION 3: serialize. Adding a whole new operation is EASY: just one more
// visitor. No existing type and no existing visitor changed. This is the open
// axis of a procedural design.
std::string serialize(const Shape& shape)
{
    return std::visit(overload{
                          [](const Circle&) { return std::string{"circle"}; },
                          [](const Square&) { return std::string{"square"}; },
                          [](const Triangle&) { return std::string{"triangle"}; },
                      },
                      shape);
}

int main()
{
    std::vector<Shape> shapes{Circle{2.3}, Square{1.2}, Triangle{3.0, 4.0}};

    std::cout << "Procedural (std::variant plus std::visit) design:\n";
    for (const auto& shape : shapes)
    {
        draw(shape);
        std::cout << "  area = " << area(shape) << ", bytes = " << serialize(shape) << '\n';
    }

    std::cout << "\nEASY axis : add a new OPER. -> one new visitor (see serialize).\n"
                 "HARD axis : add a new TYPE  -> edit the variant plus every visitor.\n";
    return 0;
}
