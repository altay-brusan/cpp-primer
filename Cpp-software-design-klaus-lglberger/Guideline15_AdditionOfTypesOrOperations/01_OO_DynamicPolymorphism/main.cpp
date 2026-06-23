/*
 * Guideline 15 - Design for the Addition of Types or Operations (OO axis)
 *
 * This is the object-oriented half of the expression problem from the book.
 * A Shape base class declares a CLOSED set of virtual operations (draw and
 * area). Each concrete shape owns its own behavior. This is dynamic
 * polymorphism, and it makes one axis of extension trivial and the other
 * axis painful:
 *
 *   - Adding a new TYPE is EASY. A Triangle is one new derived class that
 *     overrides the existing operations. No existing class is touched, and
 *     no existing code is recompiled (with the exception of main). This
 *     fulfills the Open-Closed Principle (OCP) with respect to types.
 *
 *   - Adding a new OPERATION is HARD. A serialize operation cannot be added
 *     without editing the Shape base class (a new pure virtual) AND every
 *     single derived class, even ones that may never need it. The set of
 *     operations is fixed by the base class, so the OCP is violated with
 *     respect to operations.
 *
 * The book's takeaway: with dynamic polymorphism you must choose which axis
 * stays open. Object-oriented designs keep TYPES open and OPERATIONS closed.
 * Prefer this when you expect to add types far more often than operations.
 *
 * Key notes:
 *   - The strength of OO here is the open type set: new shapes plug in by
 *     deriving and overriding, modifying nothing.
 *   - The weakness is the closed operation set: every new verb is invasive
 *     because it forces a change to the base class and to all derivatives.
 *   - The HARD direction (adding serialize) is shown in comments only, so
 *     this file stays compilable while still making the cost explicit.
 */
#include <iostream>
#include <memory>
#include <numbers>
#include <vector>

// Closed set of operations: draw and area. To add a third operation later
// you would have to edit THIS base class (the painful axis).
class Shape
{
public:
    virtual ~Shape() = default;
    virtual void draw() const = 0;
    virtual double area() const = 0;

    // Adding a new OPERATION is invasive. To support serialization you would
    // uncomment the next line, which then forces every derived class below to
    // implement it. That is the OCP violation on the operation axis:
    //   virtual std::string serialize() const = 0;
};

class Circle : public Shape
{
public:
    explicit Circle(double radius) : m_radius{radius} {}

    void draw() const override { std::cout << "Circle(r=" << m_radius << ")\n"; }
    double area() const override { return std::numbers::pi * m_radius * m_radius; }

    // If serialize were added to Shape, EVERY type below would need this too:
    //   std::string serialize() const override { return "circle"; }

private:
    double m_radius;
};

class Square : public Shape
{
public:
    explicit Square(double side) : m_side{side} {}

    void draw() const override { std::cout << "Square(s=" << m_side << ")\n"; }
    double area() const override { return m_side * m_side; }

private:
    double m_side;
};

// Adding a new TYPE is EASY: one new class, nothing else changes. This is the
// open axis of an object-oriented design.
class Triangle : public Shape
{
public:
    Triangle(double base, double height) : m_base{base}, m_height{height} {}

    void draw() const override
    {
        std::cout << "Triangle(b=" << m_base << ", h=" << m_height << ")\n";
    }
    double area() const override { return 0.5 * m_base * m_height; }

private:
    double m_base;
    double m_height;
};

// Operates through the base interface, so it needs no change when a new TYPE
// is added (contrast with the procedural switch in sample 02).
void drawAll(const std::vector<std::unique_ptr<Shape>>& shapes)
{
    for (const auto& shape : shapes)
    {
        shape->draw();
        std::cout << "  area = " << shape->area() << '\n';
    }
}

int main()
{
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(2.3));
    shapes.push_back(std::make_unique<Square>(1.2));
    // The new TYPE drops in with zero edits to existing classes:
    shapes.push_back(std::make_unique<Triangle>(3.0, 4.0));

    std::cout << "Object-oriented (dynamic polymorphism) design:\n";
    drawAll(shapes);

    std::cout << "\nEASY axis : add a new TYPE  -> one new derived class.\n"
                 "HARD axis : add a new OPER. -> edit Shape plus every class.\n";
    return 0;
}
