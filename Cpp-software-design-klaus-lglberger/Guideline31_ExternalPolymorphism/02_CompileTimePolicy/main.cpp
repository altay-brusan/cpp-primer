/*
 * Guideline 31 - Use External Polymorphism for Nonintrusive Runtime Polymorphism
 *                (compile-time strategy plus the any-type demonstration)
 *
 * Because ShapeModel is ALREADY a class template, the book points out you can
 * switch the runtime std::function strategy for a compile-time one: pass the
 * draw strategy as a second template parameter with a default. A DefaultDrawer
 * simply calls a free draw() function found by argument-dependent lookup, so the
 * only requirement on a type is: provide a free draw(const T&). Building on a
 * free function (rather than a member) inverts the dependency and lets the type
 * stay completely unaware of the concept.
 *
 * The most striking consequence: you can equip literally ANY type with
 * polymorphic behavior, nonintrusively, even a built-in like int, just by
 * providing a free draw() for it. The book offers this as a technical
 * demonstration, not a recommendation, and as a reminder that the wrapped type
 * still must honor the semantic expectations (LSP, Guideline 6).
 *
 * Key notes:
 *   - DefaultDrawer forwards to a free draw(obj); the type opts in by existing,
 *     not by inheriting. No artificial requirement is imposed on the type.
 *   - The compile-time policy removes the std::function indirection (faster) and
 *     keeps the strategy choice in exactly one place, the ShapeModel wrapper.
 *   - An int satisfies the concept once a free draw(int) exists, so a vector of
 *     unique_ptr to ShapeConcept can hold a wrapped int alongside real shapes.
 *   - This nonintrusive any-type adaptation is exactly the power Type Erasure
 *     (Guideline 32) packages behind a clean value type.
 */
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

// Plain value types, again with no base and no virtual functions.
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

// Free draw functions: the behavior lives outside the types and is found by
// argument-dependent lookup. Adding draw for a new type touches nothing else.
void draw(const Circle& c) { std::cout << "[draw] circle r=" << c.radius() << '\n'; }
void draw(const Square& s) { std::cout << "[draw] square s=" << s.side() << '\n'; }
void draw(int i) { std::cout << "[draw] int value=" << i << '\n'; }

// The external abstraction, same as sample 01.
class ShapeConcept
{
public:
    virtual ~ShapeConcept() = default;
    virtual void draw() const = 0;
};

// The default compile-time strategy: just call the free draw() for the object.
struct DefaultDrawer
{
    template <typename T>
    void operator()(const T& obj) const
    {
        draw(obj);
    }
};

// ShapeModel with the strategy as a template parameter (policy-based design).
// Note the member function calls m_drawer, not draw(), to avoid recursing into
// itself; the strategy is what reaches the free draw() function.
template <typename ShapeT, typename DrawStrategy = DefaultDrawer>
class ShapeModel : public ShapeConcept
{
public:
    explicit ShapeModel(ShapeT shape, DrawStrategy drawer = DrawStrategy{})
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
    shapes.emplace_back(std::make_unique<ShapeModel<Circle>>(Circle{2.3}));
    shapes.emplace_back(std::make_unique<ShapeModel<Square>>(Square{1.2}));

    // The astonishing part: wrap a built-in int with polymorphic behavior,
    // nonintrusively, simply because a free draw(int) exists.
    shapes.emplace_back(std::make_unique<ShapeModel<int>>(42));

    std::cout << "Compile-time strategy via a free draw() function:\n";
    for (const auto& shape : shapes)
        shape->draw();

    std::cout << "\nNo type opted into a hierarchy. Even int behaves\n"
                 "polymorphically here only because a free draw(int) was provided.\n"
                 "Behavior is attached from the outside, at the lowest level.\n";
    return 0;
}
