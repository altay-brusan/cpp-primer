/*
 * Guideline 6 - Adhere to the Expected Behavior of Abstractions (model behavior honestly)
 *
 * The fix is to stop forcing an IS-A relationship that does not hold behaviorally.
 * We do NOT make Square inherit from Rectangle. Instead we introduce an honest
 * abstraction, Shape, that promises ONLY what every shape can truly deliver: an
 * area. Shape says nothing about independent side lengths, so no subtype can
 * break that promise. Rectangle and Square are then separate Shapes: Rectangle
 * keeps the independent setWidth and setHeight (its genuine behavior), while
 * Square exposes a single setSide (its genuine behavior). Each derived type
 * fully honors the expectations of the abstraction it actually implements, so
 * the Liskov Substitution Principle holds everywhere.
 *
 * Key notes:
 *   - The Shape abstraction is minimal and meaningful: it only promises area().
 *     Both Rectangle and Square honor it, so either can stand in for a Shape.
 *   - The "set width and height independently" behavior now lives only on
 *     Rectangle, so transform() takes a Rectangle reference, not a Shape. The
 *     expectation it relies on is exactly the one Rectangle guarantees.
 *   - Because Square is no longer a Rectangle, you simply cannot pass a Square to
 *     transform(). The compiler makes the earlier misuse impossible, instead of
 *     letting it slip through and fail at run time. See the commented line in
 *     main for what would not compile.
 *   - This is the lesson of the guideline: an IS-A relationship is about honored
 *     behavior. Put each behavior in the abstraction that can truly promise it,
 *     and choose abstractions that every subtype can satisfy.
 *   - This file is the AFTER picture: the same domain, modeled so every subtype
 *     adheres to the expected behavior of its abstraction.
 */
#include <iostream>
#include <memory>
#include <vector>

// Honest abstraction: it promises ONLY an area, which every shape can deliver.
// It deliberately says nothing about how (or whether) sides can be changed.
class Shape
{
public:
    virtual ~Shape() = default;
    virtual int area() const = 0;
    virtual const char* name() const = 0;
};

// A Rectangle genuinely has two independent side lengths.
class Rectangle : public Shape
{
public:
    void setWidth(int w) { m_width = w; }
    void setHeight(int h) { m_height = h; }

    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }

    int area() const override { return m_width * m_height; }
    const char* name() const override { return "Rectangle"; }

private:
    int m_width{ 0 };
    int m_height{ 0 };
};

// A Square genuinely has a single side length. It is NOT a Rectangle, so it
// never has to break the independence promise that Rectangle makes.
class Square : public Shape
{
public:
    void setSide(int s) { m_side = s; }
    int getSide() const { return m_side; }

    int area() const override { return m_side * m_side; }
    const char* name() const override { return "Square"; }

private:
    int m_side{ 0 };
};

// This function relies on the independent-sides behavior, which only Rectangle
// promises, so it asks for a Rectangle. The expectation it depends on is always
// honored, because every Rectangle truly has independent sides.
void transform(Rectangle& rectangle)
{
    rectangle.setWidth(7);
    rectangle.setHeight(4);

    const int expected = 28; // 7 times 4
    const int actual = rectangle.area();

    std::cout << "  transform(Rectangle): width=" << rectangle.getWidth()
              << " height=" << rectangle.getHeight()
              << " area=" << actual
              << " (expected " << expected << ") -> "
              << (actual == expected ? "expectation HONORED" : "expectation BROKEN")
              << '\n';
}

// This function depends only on the Shape promise (an area), so it works for
// every Shape, present and future, without ever being surprised.
void printArea(const Shape& shape)
{
    std::cout << "  " << shape.name() << " area through Shape: " << shape.area() << '\n';
}

int main()
{
    std::cout << "Honest design (no false IS-A; Shape promises only area):\n";

    Rectangle r;
    transform(r); // relies on independent sides; Rectangle always honors it

    Square sq;
    sq.setSide(5);

    // transform(sq); // would NOT compile: a Square is not a Rectangle, so the
    //                // earlier misuse is impossible by construction.

    std::cout << "Both types honor the Shape abstraction:\n";
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Rectangle>(r));
    shapes.push_back(std::make_unique<Square>(sq));
    for (const auto& shape : shapes)
    {
        printArea(*shape);
    }

    std::cout << "\nEvery subtype now adheres to the expected behavior of its\n"
                 "abstraction: Shape promises only area() and both keep it, while\n"
                 "the independent-sides behavior lives on Rectangle alone. The LSP\n"
                 "holds, and the compiler prevents passing a Square where a true\n"
                 "Rectangle is required.\n";
    return 0;
}
