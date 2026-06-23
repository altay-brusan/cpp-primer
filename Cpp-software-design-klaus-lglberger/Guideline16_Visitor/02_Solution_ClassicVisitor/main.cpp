/*
 * Guideline 16 - The classic GoF Visitor (double dispatch via accept and visit)
 *
 * This is the AFTER picture. The Visitor design pattern keeps the OPERATION
 * axis open over a CLOSED set of types. Its intent (GoF): represent an operation
 * to be performed on the elements of an object structure, and let you define a
 * new operation without changing the classes of the elements it operates on.
 *
 * Two hierarchies cooperate:
 *   - The Shape hierarchy (Circle, Square) - the closed set of types.
 *   - The ShapeVisitor hierarchy - one abstract base with a visit() overload per
 *     concrete shape; each concrete visitor IS one operation.
 *
 * Shape gains a single virtual accept(ShapeVisitor const&). Each shape
 * implements it identically as v.visit(*this), but because the this pointer has
 * a different concrete type per shape it selects a different visit() overload.
 * That is DOUBLE DISPATCH: accept() resolves the shape type, visit() resolves
 * the operation type. Adding an operation (Draw, Serialize, Area) is now just a
 * new ShapeVisitor subclass - no edit to any shape. This extracts "operations"
 * as a variation point (SRP), which is what enables the OCP for operations.
 *
 * Key notes:
 *   - Adding an OPERATION is easy: write one new visitor, touch no shape.
 *   - TRADE-OFF: adding a TYPE is now hard. A new Triangle forces a new pure
 *     virtual visit(Triangle&) into ShapeVisitor, which every existing visitor
 *     must then implement. The pattern trades an open type axis for an open
 *     operation axis (a cyclic dependency between the two hierarchies).
 *   - visit() has a fixed return type chosen by the base, so the usual way to
 *     return a result is to store it in the visitor (see Area below).
 *   - It is intrusive (accept must be added to the base) and uses two virtual
 *     calls per operation, so it is comparatively slow; boilerplate is common
 *     because each visit() overload must exist even when logic is identical.
 */
#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Forward declarations so the visitor base can name the concrete shapes.
class Circle;
class Square;

// The operation abstraction: one visit() overload per concrete shape.
class ShapeVisitor
{
public:
    virtual ~ShapeVisitor() = default;
    virtual void visit(const Circle&) const = 0;
    virtual void visit(const Square&) const = 0;
    // A new shape would force a new pure visit() overload HERE (the trade-off).
};

// The element base: gains exactly one new virtual, accept().
class Shape
{
public:
    virtual ~Shape() = default;
    virtual void accept(const ShapeVisitor& v) const = 0;
};

class Circle : public Shape
{
public:
    explicit Circle(double radius) : m_radius(radius) {}

    // Identical body in every shape, but *this has a different concrete type,
    // so it triggers a different visit() overload. That is double dispatch.
    void accept(const ShapeVisitor& v) const override { v.visit(*this); }

    double radius() const { return m_radius; }

private:
    double m_radius;
};

class Square : public Shape
{
public:
    explicit Square(double side) : m_side(side) {}

    void accept(const ShapeVisitor& v) const override { v.visit(*this); }

    double side() const { return m_side; }

private:
    double m_side;
};

// Operation 1: Draw. A new operation is just a new visitor - no shape changes.
class Draw : public ShapeVisitor
{
public:
    void visit(const Circle& c) const override
    {
        std::cout << "Circle(r=" << c.radius() << ")\n";
    }
    void visit(const Square& s) const override
    {
        std::cout << "Square(s=" << s.side() << ")\n";
    }
};

// Operation 2: Serialize. Added without touching Shape, Circle, or Square.
class Serialize : public ShapeVisitor
{
public:
    void visit(const Circle& c) const override
    {
        std::cout << "[circle radius=" << c.radius() << "]\n";
    }
    void visit(const Square& s) const override
    {
        std::cout << "[square side=" << s.side() << "]\n";
    }
};

// Operation 3: Area. visit() returns void (fixed by the base), so the result is
// stored in the visitor and read afterwards - the usual Visitor workaround.
class Area : public ShapeVisitor
{
public:
    void visit(const Circle& c) const override
    {
        m_total += 3.14159265 * c.radius() * c.radius();
    }
    void visit(const Square& s) const override
    {
        m_total += s.side() * s.side();
    }
    double total() const { return m_total; }

private:
    mutable double m_total{0.0};
};

int main()
{
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(2.3));
    shapes.push_back(std::make_unique<Square>(1.2));
    shapes.push_back(std::make_unique<Circle>(4.1));

    std::cout << "Draw (operation as a visitor):\n";
    for (const auto& shape : shapes) { shape->accept(Draw{}); }

    std::cout << "\nSerialize (a second operation, zero shape edits):\n";
    for (const auto& shape : shapes) { shape->accept(Serialize{}); }

    Area area;
    for (const auto& shape : shapes) { shape->accept(area); }
    std::cout << "\nArea (result stored in the visitor): total = "
              << area.total() << '\n';

    std::cout << "\nAdding an OPERATION = one new visitor, no shape touched.\n"
                 "Trade-off: adding a TYPE (Triangle) would force a new\n"
                 "visit() into ShapeVisitor and into EVERY visitor above.\n";
    return 0;
}
