/*
 * Guideline 19 - Use Strategy to Isolate How Things Are Done
 *                (policy-based design: the compile-time form of Strategy)
 *
 * The book notes that Strategy is not limited to dynamic polymorphism: its
 * intent maps perfectly onto static polymorphism using templates, a style
 * Andrei Alexandrescu named policy-based design. The std::sort comparator and
 * the Deleter of std::unique_ptr are exactly this idea: a varying behavior
 * injected through a template parameter.
 *
 * Here the drawing strategy is supplied as a TEMPLATE ARGUMENT instead of a
 * unique_ptr. Circle becomes Circle<DrawPolicy>. The HOW is still isolated and
 * interchangeable, but it is selected at compile time, so the strategy call has
 * no virtual indirection.
 *
 * Key notes:
 *   - The policy is injected via a template parameter, the static-polymorphism
 *     twin of constructor injection. Same intent as the runtime Strategy: the
 *     drawing detail is extracted and made interchangeable.
 *   - No virtual call and no allocation for the strategy, so there is no runtime
 *     penalty, which the book highlights as the main payoff over the OO form.
 *   - The trade-off: each policy yields a distinct type (Circle<ConsoleStrategy>
 *     versus Circle<OpenGLStrategy>), so a single instance cannot swap its
 *     strategy at runtime, and the code tends to live in headers.
 *   - Adding a NEW backend (SvgStrategy below) is still pure extension: write
 *     one policy class, touch no shape and no other policy.
 */
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

// Shapes share a runtime base only so they can sit in one container.
class Shape
{
public:
    virtual ~Shape() = default;
    virtual void draw() const = 0;
};

// A shape carries its drawing policy as a template argument. The policy is the
// isolated variation point, chosen at compile time.
template <typename DrawPolicy>
class Circle : public Shape
{
public:
    explicit Circle(double radius, DrawPolicy drawer = {})
        : m_radius(radius), m_drawer(std::move(drawer))
    {
    }

    void draw() const override { m_drawer.draw(*this); }
    const char* name() const { return "circle"; }
    double dimension() const { return m_radius; }

private:
    double m_radius;
    DrawPolicy m_drawer;
};

template <typename DrawPolicy>
class Square : public Shape
{
public:
    explicit Square(double side, DrawPolicy drawer = {})
        : m_side(side), m_drawer(std::move(drawer))
    {
    }

    void draw() const override { m_drawer.draw(*this); }
    const char* name() const { return "square"; }
    double dimension() const { return m_side; }

private:
    double m_side;
    DrawPolicy m_drawer;
};

// Policies: stateless strategies selected at compile time. Each draw() is a
// template so one policy can serve any shape that exposes name()/dimension().

struct ConsoleStrategy
{
    template <typename S>
    void draw(const S& s) const
    {
        std::cout << "[console] " << s.name() << " dim=" << s.dimension() << '\n';
    }
};

struct OpenGLStrategy
{
    template <typename S>
    void draw(const S& s) const
    {
        std::cout << "[opengl] " << s.name() << " dim=" << s.dimension() << '\n';
    }
};

// A brand new backend, added WITHOUT editing any shape or other policy.
struct SvgStrategy
{
    template <typename S>
    void draw(const S& s) const
    {
        std::cout << "[svg] <" << s.name() << " dim=\"" << s.dimension() << "\"/>\n";
    }
};

int main()
{
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle<ConsoleStrategy>>(2.3));
    shapes.push_back(std::make_unique<Square<OpenGLStrategy>>(1.2));
    shapes.push_back(std::make_unique<Circle<SvgStrategy>>(4.1)); // freshly added backend

    std::cout << "Strategy injected at compile time (policy-based design):\n";
    for (const auto& shape : shapes)
        shape->draw();

    std::cout << "\nThe drawing policy is a template argument, so there is no\n"
                 "virtual call into the strategy. Same Strategy intent, resolved\n"
                 "statically: the compile-time form isolates HOW a shape is drawn.\n";
    return 0;
}
