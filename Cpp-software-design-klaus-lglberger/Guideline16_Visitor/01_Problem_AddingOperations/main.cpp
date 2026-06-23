/*
 * Guideline 16 - Adding operations to a closed shape hierarchy (the pain)
 *
 * This is the BEFORE picture for the Visitor design pattern. We have a Shape
 * base class with a small, fixed set of concrete shapes (Circle and Square) and
 * we treat that set as CLOSED: we are sure we already have every shape we will
 * ever need. What we expect instead is an OPEN set of OPERATIONS - draw today,
 * then serialize, rotate, translate, and more later, possibly written by people
 * who cannot edit this file.
 *
 * Object-oriented design is great at adding TYPES but weak at adding
 * OPERATIONS. Here every new operation is a new virtual function in the Shape
 * base class, which must then be implemented in every derived class. That edit
 * to existing, working code is exactly what the Open-Closed Principle (OCP)
 * warns against, and not everyone is even able to change the base class.
 *
 * This file compiles and runs with TWO operations already baked in (draw and
 * area) to make the cost visible: notice that each operation appears once in the
 * base and once in EVERY shape. A third operation (serialize) would repeat that
 * same scattering, shown in comments so the file still builds.
 *
 * Key notes:
 *   - Adding an operation means editing the base class plus Circle plus Square.
 *     The change grows with the number of shapes, not with the operation.
 *   - A pure virtual operation forces every existing and future derived shape
 *     to implement it, so you create work for other people too.
 *   - A default implementation rarely makes sense (a default serialize is hard),
 *     so the choice is between intrusive edits or a Liskov violation.
 *   - The operation logic is spread across many classes, so reading or changing
 *     one operation means hopping through the whole hierarchy.
 */
#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Shape
{
public:
    virtual ~Shape() = default;

    // Operation 1: every shape must know how to draw itself.
    virtual void draw() const = 0;

    // Operation 2: added later - note it had to appear here AND in every shape.
    virtual double area() const = 0;

    // Operation 3 (serialize) would have to be ADDED here as well, then
    // implemented again in Circle and Square below. That is the pain:
    //   virtual std::string serialize() const = 0;
};

class Circle : public Shape
{
public:
    explicit Circle(double radius) : m_radius(radius) {}

    void draw() const override { std::cout << "Circle(r=" << m_radius << ")\n"; }

    double area() const override { return 3.14159265 * m_radius * m_radius; }

    // A new operation forces a new override HERE too:
    //   std::string serialize() const override { ... }

    double radius() const { return m_radius; }

private:
    double m_radius;
};

class Square : public Shape
{
public:
    explicit Square(double side) : m_side(side) {}

    void draw() const override { std::cout << "Square(s=" << m_side << ")\n"; }

    double area() const override { return m_side * m_side; }

    // ...and the SAME new operation forces yet another override HERE:
    //   std::string serialize() const override { ... }

    double side() const { return m_side; }

private:
    double m_side;
};

int main()
{
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(2.3));
    shapes.push_back(std::make_unique<Square>(1.2));
    shapes.push_back(std::make_unique<Circle>(4.1));

    std::cout << "Closed set of operations (draw, area) baked into the base:\n";
    for (const auto& shape : shapes)
    {
        shape->draw();
        std::cout << "  area = " << shape->area() << '\n';
    }

    std::cout << "\nProblem: each new operation (serialize, rotate, ...) means\n"
                 "editing the Shape base AND every derived class. OOP makes\n"
                 "adding TYPES easy but adding OPERATIONS invasive.\n";
    return 0;
}
