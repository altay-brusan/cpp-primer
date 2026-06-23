/*
 * Guideline 31 - Use External Polymorphism for Nonintrusive Runtime Polymorphism
 *                (the External Polymorphism design pattern: behavior lives outside the types)
 *
 * Strategy (Guideline 19) extracted HOW a shape is drawn, but the shapes still
 * had to carry a draw() member and inherit from a Shape base. The book argues
 * drawing is an isolated aspect: shapes should be oblivious to the fact that they
 * can be drawn at all. External Polymorphism takes the separation of concerns one
 * step further and extracts the ENTIRE polymorphic behavior out of the types.
 *
 * Intent (Cleeland, Schmidt, Harrison, 1996): allow C++ classes unrelated by
 * inheritance and having no virtual functions to be treated polymorphically.
 *
 * The trick: there is no Shape base class anymore. Circle and Square are plain
 * value types with no base and no virtual functions. A SEPARATE, external
 * hierarchy carries the behavior: an abstract ShapeConcept declares the
 * operations, and a ShapeModel template adapts any concrete type T to that
 * concept by storing a T and forwarding the virtual call to an injected
 * strategy. ShapeModel is the only class that ever derives from ShapeConcept.
 *
 * Key notes:
 *   - Circle and Square know nothing about drawing, ShapeConcept, or graphics
 *     libraries. The behavior is bolted on from the outside, nonintrusively.
 *   - ShapeModel stores the shape by composition (Guideline 20), not by
 *     inheritance, and delegates draw() to a std::function strategy
 *     (Guideline 19 and 23): how to draw is decoupled from what is drawn.
 *   - We store vector of unique_ptr to ShapeConcept and draw every element
 *     polymorphically, yet the value types never opted in to a hierarchy.
 *   - Adding a brand new third-party type needs no edit to it: just instantiate
 *     ShapeModel for it. That is the Open-Closed Principle, nonintrusively.
 *   - This external Concept plus Model hierarchy is the foundation of Type
 *     Erasure (Guideline 32), which hides these pointers behind a value type.
 */
#include <functional>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

// Plain value types: no base class, no virtual functions, no idea about drawing.
class Circle
{
public:
    explicit Circle(double radius) : m_radius(radius) {}
    double radius() const { return m_radius; }

private:
    double m_radius;
};

class Square
{
public:
    explicit Square(double side) : m_side(side) {}
    double side() const { return m_side; }

private:
    double m_side;
};

// The external hierarchy. ShapeConcept is the abstraction that holds the whole
// set of polymorphic operations (here just draw); it replaces the old Shape base.
class ShapeConcept
{
public:
    virtual ~ShapeConcept() = default;
    virtual void draw() const = 0;
};

// ShapeModel adapts ANY type ShapeT to ShapeConcept. It is the only class that
// inherits from ShapeConcept. It stores the concrete shape by value and forwards
// the virtual draw() to an injected strategy (here a std::function).
template <typename ShapeT, typename DrawStrategy = std::function<void(const ShapeT&)>>
class ShapeModel : public ShapeConcept
{
public:
    ShapeModel(ShapeT shape, DrawStrategy drawer)
        : m_shape(std::move(shape)), m_drawer(std::move(drawer))
    {
    }

    void draw() const override { m_drawer(m_shape); }

private:
    ShapeT m_shape;
    DrawStrategy m_drawer;
};

int main()
{
    using Shapes = std::vector<std::unique_ptr<ShapeConcept>>;

    Shapes shapes;

    // Each model pairs a plain shape with a drawing strategy. The strategy could
    // hold colors, textures, or a backend handle; here it just prints to console.
    shapes.emplace_back(std::make_unique<ShapeModel<Circle>>(
        Circle{2.3},
        [](const Circle& c) { std::cout << "[draw] circle r=" << c.radius() << '\n'; }));

    shapes.emplace_back(std::make_unique<ShapeModel<Square>>(
        Square{1.2},
        [](const Square& s) { std::cout << "[draw] square s=" << s.side() << '\n'; }));

    shapes.emplace_back(std::make_unique<ShapeModel<Circle>>(
        Circle{4.1},
        [](const Circle& c) { std::cout << "[draw] circle r=" << c.radius() << '\n'; }));

    std::cout << "Behavior was added from OUTSIDE the value types:\n";
    for (const auto& shape : shapes)
        shape->draw();

    std::cout << "\nCircle and Square have no base class and no virtual functions,\n"
                 "yet they are drawn polymorphically through the external\n"
                 "ShapeConcept hierarchy. The shapes never knew they were drawable.\n";
    return 0;
}
