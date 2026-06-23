/*
 * Guideline 6 - Adhere to the Expected Behavior of Abstractions (the LSP violation)
 *
 * This is the classic Rectangle and Square example from the book. A Rectangle is
 * designed as a base class abstraction for rectangles: it owns two side lengths,
 * width and height, and the abstraction makes an implicit but very real promise -
 * the two sides can be set INDEPENDENTLY. Setting the width must not change the
 * height. Square then publicly inherits from Rectangle because "a square is a
 * rectangle" in geometry. To keep its own invariant (all sides equal) a Square
 * has to override setWidth and setHeight so each one changes BOTH sides. By
 * protecting its own invariant the Square breaks the expectation of the base
 * class, which is a violation of the Liskov Substitution Principle (LSP). The
 * code compiles and runs, but a Square cannot be used everywhere a Rectangle is
 * expected, so the inheritance does not express a true IS-A relationship.
 *
 * Key notes:
 *   - The abstraction Rectangle promises: after setWidth then setHeight, the
 *     result of getWidth is unchanged. Square cannot keep that promise.
 *   - transform() sets width to 7 and height to 4 and expects an area of 28
 *     (7 times 4). For a real Rectangle the expectation holds; for a Square the
 *     second call overwrites the first, so the area becomes 16 (4 times 4).
 *   - The book uses an assert that fires and aborts the process. Here we instead
 *     PRINT the expected versus the actual value, so the broken expectation is
 *     visible while the program still runs cleanly.
 *   - Geometry says a square is a rectangle, but the LSP IS-A relationship is
 *     about behavior, not mathematics. As long as setWidth and setHeight are
 *     independent, a Square will always violate the expectation.
 *   - This file is the BEFORE picture: bad design that compiles and runs.
 */
#include <iostream>

// The abstraction. Its expected behavior: width and height are independent.
class Rectangle
{
public:
    virtual ~Rectangle() = default;

    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }

    virtual void setWidth(int w) { m_width = w; }
    virtual void setHeight(int h) { m_height = h; }

    virtual int getArea() const { return m_width * m_height; }

private:
    int m_width{ 0 };
    int m_height{ 0 };
};

// A square has only one side length, so to keep its invariant (sides equal) it
// must override both setters to change BOTH members. That is exactly what breaks
// the independence promise of the Rectangle abstraction.
class Square : public Rectangle
{
public:
    void setWidth(int w) override
    {
        Rectangle::setWidth(w);
        Rectangle::setHeight(w); // forced to keep the invariant
    }

    void setHeight(int h) override
    {
        Rectangle::setWidth(h); // forced to keep the invariant
        Rectangle::setHeight(h);
    }
};

// Calling code depends only on the Rectangle abstraction. It assumes the two
// sides are independent, so after these two calls it expects an area of 28.
void transform(Rectangle& rectangle)
{
    rectangle.setWidth(7);
    rectangle.setHeight(4);

    const int expected = 28; // 7 times 4
    const int actual = rectangle.getArea();

    std::cout << "  after setWidth(7), setHeight(4): "
              << "width=" << rectangle.getWidth()
              << " height=" << rectangle.getHeight()
              << " area=" << actual
              << " (expected " << expected << ") -> "
              << (actual == expected ? "expectation HONORED" : "expectation BROKEN")
              << '\n';
}

int main()
{
    std::cout << "LSP violation (Square inherits from Rectangle):\n";

    std::cout << "Plain Rectangle through the abstraction:\n";
    Rectangle r;
    transform(r);

    std::cout << "Square through the SAME abstraction:\n";
    Square s;
    transform(s);

    std::cout << "\nProblem: a reference to Square is implicitly a reference to\n"
                 "Rectangle, so transform() accepts it - but the Square cannot\n"
                 "keep the independence promise of the base class. The second\n"
                 "setter overwrites the first, the area is 16 instead of 28, and\n"
                 "the abstraction's expectation is violated. That is the LSP\n"
                 "violation: the hierarchy does not express a true IS-A.\n";
    return 0;
}
