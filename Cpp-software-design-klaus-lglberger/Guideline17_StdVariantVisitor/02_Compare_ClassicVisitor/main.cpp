/*
 * Guideline 17 - Contrast: the classic Gang-of-Four Visitor (the boilerplate)
 *
 * This sample exists only to make the trade-off concrete. It implements the SAME
 * draw-and-area behavior as sample 01, but in the intrusive object-oriented
 * Visitor style the book describes in Guideline 16. Compare the machinery:
 *
 *   - A ShapeVisitor base class declaring one pure virtual visit per shape.
 *   - A Shape base class with a pure virtual accept hook.
 *   - Every concrete shape must derive from Shape and implement accept, which
 *     calls back into the visitor (the double dispatch).
 *   - Every operation is a class deriving from ShapeVisitor.
 *   - Heterogeneous storage needs owning pointers, here std::unique_ptr<Shape>,
 *     so we are back to allocation and reference semantics.
 *
 * The behavior is identical to the variant version, but look at how much more
 * code, coupling, and indirection it takes. The classic Visitor also carries a
 * cyclic dependency: Shape depends on ShapeVisitor (to declare accept) and
 * ShapeVisitor depends on every concrete shape (to declare each visit), so the
 * abstraction and its alternatives are knotted together. The std::variant
 * solution in sample 01 has no such cycle.
 *
 * Key notes:
 *   - Same result, far more scaffolding: base classes, accept, virtual visit,
 *     and owning pointers, none of which the variant version needs.
 *   - Double dispatch adds runtime indirection; the book benchmarks the classic
 *     Visitor as the slowest of the approaches it measures.
 *   - The one thing this style buys you is an open TYPE axis: a new shape derives
 *     from Shape and adds one accept, without editing a central variant. That is
 *     the mirror-image trade-off of the value-based design.
 *   - This file is the BEFORE picture; sample 01 is the recommended AFTER.
 */
#include <iostream>
#include <memory>
#include <numbers>
#include <vector>

class Circle;
class Square;

// The Visitor base class: one pure virtual visit per concrete shape. Adding a
// new shape forces a new pure virtual here, recompiling every visitor.
class ShapeVisitor
{
public:
    virtual ~ShapeVisitor() = default;
    virtual void visit(const Circle&) const = 0;
    virtual void visit(const Square&) const = 0;
};

// The Shape base class: the intrusive accept hook every shape must implement.
class Shape
{
public:
    virtual ~Shape() = default;
    virtual void accept(const ShapeVisitor& v) const = 0;
};

class Circle : public Shape
{
public:
    explicit Circle(double r) : radius_{r} {}
    double radius() const { return radius_; }
    // The shape calls back into the visitor: the second of the two dispatches.
    void accept(const ShapeVisitor& v) const override { v.visit(*this); }

private:
    double radius_;
};

class Square : public Shape
{
public:
    explicit Square(double s) : side_{s} {}
    double side() const { return side_; }
    void accept(const ShapeVisitor& v) const override { v.visit(*this); }

private:
    double side_;
};

// OPERATION 1: draw, written as a whole class deriving from ShapeVisitor.
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

// OPERATION 2: area. A second visitor class. It cannot simply return a double
// through the fixed visit signature, so it stashes the result in a member, a
// common awkwardness of the classic style.
class Area : public ShapeVisitor
{
public:
    void visit(const Circle& c) const override
    {
        result_ = std::numbers::pi * c.radius() * c.radius();
    }
    void visit(const Square& s) const override
    {
        result_ = s.side() * s.side();
    }
    double result() const { return result_; }

private:
    mutable double result_{0.0};
};

int main()
{
    // Heterogeneous storage needs owning pointers: reference semantics return.
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(2.3));
    shapes.push_back(std::make_unique<Square>(1.2));
    shapes.push_back(std::make_unique<Circle>(4.1));

    std::cout << "Classic Gang-of-Four Visitor (base classes plus accept):\n";
    const Draw drawer;
    for (const auto& shape : shapes)
    {
        shape->accept(drawer);     // double dispatch for operation 1
        Area areaOp;
        shape->accept(areaOp);     // double dispatch for operation 2
        std::cout << "  area = " << areaOp.result() << '\n';
    }

    std::cout << "\nSame behavior as sample 01, but with a Shape base class, a\n"
                 "ShapeVisitor base class, an accept hook, virtual dispatch, and\n"
                 "owning pointers. The std::variant version needs none of these.\n";
    return 0;
}
