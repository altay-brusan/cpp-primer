/*
 * Guideline 23 - Prefer a Value-Based Implementation of Strategy
 *                (Strategy via std::function, no DrawStrategy base class)
 *
 * Guideline 19 implemented Strategy with an inheritance hierarchy: a
 * DrawStrategy base class per shape, injected as a std::unique_ptr. That works,
 * but it drags in reference semantics, pointers, and lifetime management. The
 * book asks: can we apply the value-semantics wisdom of Guideline 22 here? Yes,
 * by drawing on the abstracting power of std::function.
 *
 * std::function is a value, a type-erased callable. It can hold ANY callable
 * that matches its function type: a free function, a function object, or a
 * lambda. So instead of a DrawStrategy base class with one virtual draw(), each
 * shape simply stores a std::function as its drawing strategy. No base class, no
 * pointers, no allocation forced on the caller. The strategy is injected by
 * value and moved into the data member, which the book shows is an elegant
 * compromise: an lvalue costs one copy plus one move, an rvalue costs two moves.
 *
 * Key notes:
 *   - The using alias DrawStrategy is now std::function, not a base class. It
 *     abstracts a single callable, exactly what one virtual function provided.
 *   - Any callable form is accepted: free function, functor, or lambda. Authors
 *     of a backend no longer have to derive from anything.
 *   - Value semantics: copying a shape deep-copies its strategy, so there is no
 *     shared mutable state and no dangling-pointer worry.
 *   - A default-constructed std::function is empty; calling it throws
 *     std::bad_function_call. We guard against that in the constructor.
 *   - std::function replaces ONE virtual function well. Several varying aspects
 *     would need several std::function members (see sample 03).
 */
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

// The shape base keeps a single virtual draw(); shapes stay simple primitives.
class Shape
{
public:
    virtual ~Shape() = default;
    virtual void draw() const = 0;
};

// Circle owns a value-based drawing strategy. No DrawStrategy base class exists.
class Circle : public Shape
{
public:
    // The strategy is just a callable taking a Circle and returning nothing.
    using DrawStrategy = std::function<void(const Circle&)>;

    Circle(double radius, DrawStrategy drawer)
        : m_radius(radius), m_drawer(std::move(drawer))
    {
        if (!m_drawer)
            throw std::invalid_argument("Circle needs a non-empty draw strategy");
    }

    void draw() const override { m_drawer(*this); }
    double radius() const { return m_radius; }

private:
    double m_radius;
    DrawStrategy m_drawer;
};

class Square : public Shape
{
public:
    using DrawStrategy = std::function<void(const Square&)>;

    Square(double side, DrawStrategy drawer)
        : m_side(side), m_drawer(std::move(drawer))
    {
        if (!m_drawer)
            throw std::invalid_argument("Square needs a non-empty draw strategy");
    }

    void draw() const override { m_drawer(*this); }
    double side() const { return m_side; }

private:
    double m_side;
    DrawStrategy m_drawer;
};

// A backend may be a free function ...
void consoleDrawCircle(const Circle& c)
{
    std::cout << "[free fn]  circle r=" << c.radius() << '\n';
}

// ... or a function object (a functor), here carrying its own state (a label).
class OpenGLSquareStrategy
{
public:
    explicit OpenGLSquareStrategy(std::string label) : m_label(std::move(label)) {}

    void operator()(const Square& s) const
    {
        std::cout << "[functor " << m_label << "] square s=" << s.side() << '\n';
    }

private:
    std::string m_label;
};

int main()
{
    std::vector<Circle> circles;
    std::vector<Square> squares;

    // 1) Inject a free function as the strategy.
    circles.emplace_back(2.3, consoleDrawCircle);

    // 2) Inject a lambda directly: no class, no derivation required.
    circles.emplace_back(4.1, [](const Circle& c) {
        std::cout << "[lambda]   svg <circle r=\"" << c.radius() << "\"/>\n";
    });

    // 3) Inject a stateful function object.
    squares.emplace_back(1.2, OpenGLSquareStrategy{"green"});

    std::cout << "Strategy held by value as std::function (no base class):\n";
    for (const auto& c : circles)
        c.draw();
    for (const auto& s : squares)
        s.draw();

    // Value semantics: copying a shape deep-copies its strategy. The copy is
    // fully independent; there is no shared pointer and nothing to dangle.
    Circle original = circles.front();
    Circle clone = original;
    std::cout << "\nA copied shape carries an independent copy of its strategy:\n";
    clone.draw();

    std::cout << "\nAny callable (function, functor, lambda) plugs in by value.\n"
                 "No DrawStrategy hierarchy, no unique_ptr, no lifetime worries.\n";
    return 0;
}
