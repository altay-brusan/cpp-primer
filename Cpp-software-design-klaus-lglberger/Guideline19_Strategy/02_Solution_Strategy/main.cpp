/*
 * Guideline 19 - Use Strategy to Isolate How Things Are Done
 *                (the Strategy design pattern: inject HOW)
 *
 * The same graphics example, redesigned. The drawing detail is extracted into a
 * separate, injectable strategy object, so the behavior can vary independently
 * of the shape. The book's intent for Strategy is exactly this: define a family
 * of algorithms, encapsulate each, and make them interchangeable so the
 * algorithm varies independently from the clients that use it.
 *
 * Following the book's advice, the strategy is a CLASS TEMPLATE,
 * DrawStrategy<T>, with one interface per shape type (DrawStrategy<Circle>,
 * DrawStrategy<Square>). That avoids the artificial coupling a single shared
 * DrawStrategy base would create, where adding a Triangle would force Circle and
 * Square to recompile. Each shape owns a unique_ptr to its strategy, supplied
 * through the constructor: dependency injection.
 *
 * Key notes:
 *   - The HOW (console, OpenGL, SVG) lives in strategy classes, not in the
 *     shapes. A shape's draw() merely forwards to its injected strategy.
 *   - Switching backend is now a local change: hand a shape a different strategy.
 *     A setter even lets a single instance change its drawing at runtime.
 *   - Adding a NEW backend (SvgCircleStrategy below) touches no shape and no
 *     other strategy: open for extension, closed for modification.
 *   - One strategy interface per shape keeps types decoupled, so new shape types
 *     can still be added freely. That preserves the strength of OOP.
 *   - Strategy isolates a single operation's detail; a second varying operation
 *     (serialize) would get its own strategy member, not more subclasses.
 */
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

// A shape stays a simple geometric primitive: it knows nothing about backends.
class Shape
{
public:
    virtual ~Shape() = default;
    virtual void draw() const = 0;
};

// One strategy interface per shape type, generated from a single template.
// This is the variation point the book tells us to extract.
template <typename T>
class DrawStrategy
{
public:
    virtual ~DrawStrategy() = default;
    virtual void draw(const T& shape) const = 0;
};

// A circle owns its drawing strategy and forwards draw() to it.
class Circle : public Shape
{
public:
    Circle(double radius, std::unique_ptr<DrawStrategy<Circle>> drawer)
        : m_radius(radius), m_drawer(std::move(drawer))
    {
    }

    void draw() const override { m_drawer->draw(*this); }
    void setDrawer(std::unique_ptr<DrawStrategy<Circle>> drawer) { m_drawer = std::move(drawer); }
    double radius() const { return m_radius; }

private:
    double m_radius;
    std::unique_ptr<DrawStrategy<Circle>> m_drawer;
};

class Square : public Shape
{
public:
    Square(double side, std::unique_ptr<DrawStrategy<Square>> drawer)
        : m_side(side), m_drawer(std::move(drawer))
    {
    }

    void draw() const override { m_drawer->draw(*this); }
    void setDrawer(std::unique_ptr<DrawStrategy<Square>> drawer) { m_drawer = std::move(drawer); }
    double side() const { return m_side; }

private:
    double m_side;
    std::unique_ptr<DrawStrategy<Square>> m_drawer;
};

// Concrete strategies: the HOW, isolated and reusable -------------------

class ConsoleCircleStrategy : public DrawStrategy<Circle>
{
public:
    void draw(const Circle& c) const override
    {
        std::cout << "[console] circle r=" << c.radius() << '\n';
    }
};

class OpenGLCircleStrategy : public DrawStrategy<Circle>
{
public:
    void draw(const Circle& c) const override
    {
        std::cout << "[opengl] circle r=" << c.radius() << '\n';
    }
};

class ConsoleSquareStrategy : public DrawStrategy<Square>
{
public:
    void draw(const Square& s) const override
    {
        std::cout << "[console] square s=" << s.side() << '\n';
    }
};

class OpenGLSquareStrategy : public DrawStrategy<Square>
{
public:
    void draw(const Square& s) const override
    {
        std::cout << "[opengl] square s=" << s.side() << '\n';
    }
};

// A brand new backend, added WITHOUT editing any shape or other strategy.
class SvgCircleStrategy : public DrawStrategy<Circle>
{
public:
    void draw(const Circle& c) const override
    {
        std::cout << "[svg] <circle r=\"" << c.radius() << "\"/>\n";
    }
};

int main()
{
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(2.3, std::make_unique<ConsoleCircleStrategy>()));
    shapes.push_back(std::make_unique<Square>(1.2, std::make_unique<OpenGLSquareStrategy>()));
    shapes.push_back(std::make_unique<Circle>(4.1, std::make_unique<OpenGLCircleStrategy>()));

    std::cout << "Strategy injected per shape (the HOW is decoupled):\n";
    for (const auto& shape : shapes)
        shape->draw();

    // The same Circle can switch its drawing at runtime: just swap the strategy.
    Circle c{5.0, std::make_unique<ConsoleCircleStrategy>()};
    std::cout << "\nSame circle, swapping the strategy at runtime:\n";
    c.draw();
    c.setDrawer(std::make_unique<SvgCircleStrategy>()); // the freshly added backend
    c.draw();

    std::cout << "\nSvg was added by writing one new strategy class. No shape and\n"
                 "no other strategy changed: the drawing detail is isolated and\n"
                 "interchangeable. Strategy isolates HOW a shape is drawn.\n";
    return 0;
}
