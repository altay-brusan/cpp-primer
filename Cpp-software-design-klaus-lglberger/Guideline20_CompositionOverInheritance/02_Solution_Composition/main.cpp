/*
 * Guideline 20 - Favor Composition over Inheritance (compose the dimensions)
 *
 * The same two varying dimensions as sample 01 - WHAT we draw and HOW we draw
 * it - but now only ONE of them stays in a hierarchy while the other is brought
 * in by composition. A Shape HAS-A DrawBackend: the shape owns its geometry and
 * delegates the rendering to a backend it holds as a data member. This is the
 * Strategy idea, and as the book stresses, Strategy works because of the
 * aggregation of a data member, not because of the inheritance of strategies.
 * "Delegate to services: has-a trumps is-a."
 *
 * Key notes:
 *   - The growth is additive now: M shapes plus N backends, not M times N. Two
 *     shapes and three backends give all six renderings from 2 plus 3 classes.
 *   - The dimensions vary independently. A new backend (SVGBackend below) works
 *     with every existing shape; a new shape (Triangle below) works with every
 *     existing backend. Neither addition forces edits to the other dimension.
 *   - Backends are shape-agnostic: they render generic rows, so they never need
 *     to know about Circle or Square. Shapes are backend-agnostic: they build
 *     their own rows and let the held backend decide the output style.
 *   - Inheritance still appears (the thin Shape hierarchy), but it only enables
 *     polymorphic use. The behavior that varies is composed in, not inherited -
 *     exactly how many design patterns are built.
 */
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

// Dimension HOW: the composed strategy. A backend renders generic rows and
// knows nothing about any specific shape, so shapes can be added freely.
class DrawBackend
{
public:
    virtual ~DrawBackend() = default;
    virtual void render(std::string_view title, const std::vector<std::string>& rows) const = 0;
};

class ConsoleBackend : public DrawBackend
{
public:
    void render(std::string_view title, const std::vector<std::string>& rows) const override
    {
        std::cout << "Console: " << title << '\n';
        for (const auto& row : rows)
        {
            std::cout << "  " << row << '\n';
        }
    }
};

class OpenGLBackend : public DrawBackend
{
public:
    void render(std::string_view title, const std::vector<std::string>& rows) const override
    {
        std::cout << "OpenGL: glBegin " << title << '\n';
        for (const auto& row : rows)
        {
            std::cout << "  glVertexRow(\"" << row << "\")\n";
        }
        std::cout << "  glEnd\n";
    }
};

// A THIRD backend added later. It needs no shape edits at all.
class SvgBackend : public DrawBackend
{
public:
    void render(std::string_view title, const std::vector<std::string>& rows) const override
    {
        std::cout << "SVG: <g label=\"" << title << "\">\n";
        for (const auto& row : rows)
        {
            std::cout << "  <text>" << row << "</text>\n";
        }
        std::cout << "  </g>\n";
    }
};

// Dimension WHAT: a thin shape hierarchy. Each shape HAS-A backend (composition)
// and asks it to render the shape's own rows. The backend is chosen at runtime.
class Shape
{
public:
    explicit Shape(std::shared_ptr<DrawBackend> backend) : m_backend(std::move(backend)) {}
    virtual ~Shape() = default;
    virtual void draw() const = 0;

protected:
    std::shared_ptr<DrawBackend> m_backend;
};

class Circle : public Shape
{
public:
    Circle(double radius, std::shared_ptr<DrawBackend> backend)
        : Shape(std::move(backend)), m_radius(radius) {}

    void draw() const override
    {
        m_backend->render("Circle r=" + std::to_string(static_cast<int>(m_radius)),
                          {" oo ", "o  o", " oo "});
    }

private:
    double m_radius;
};

class Square : public Shape
{
public:
    Square(double side, std::shared_ptr<DrawBackend> backend)
        : Shape(std::move(backend)), m_side(side) {}

    void draw() const override
    {
        m_backend->render("Square s=" + std::to_string(static_cast<int>(m_side)),
                          {"+--+", "|  |", "+--+"});
    }

private:
    double m_side;
};

// A THIRD shape added later. It works with EVERY backend, old and new.
class Triangle : public Shape
{
public:
    Triangle(double base, std::shared_ptr<DrawBackend> backend)
        : Shape(std::move(backend)), m_base(base) {}

    void draw() const override
    {
        m_backend->render("Triangle b=" + std::to_string(static_cast<int>(m_base)),
                          {"  ^  ", " / \\ ", "/___\\"});
    }

private:
    double m_base;
};

int main()
{
    // The backends are created once and shared by any shape.
    auto console = std::make_shared<ConsoleBackend>();
    auto opengl  = std::make_shared<OpenGLBackend>();
    auto svg     = std::make_shared<SvgBackend>();

    std::cout << "Composition (a shape HAS-A backend):\n\n";

    // The same shape "what" reused across different backend "how".
    Circle{2.0, console}.draw();
    Circle{2.0, opengl}.draw();

    // The same backend reused across different shapes.
    Square{3.0, console}.draw();

    // The NEW shape (Triangle) works with an OLD backend, no backend edits.
    Triangle{4.0, opengl}.draw();

    // The NEW backend (SVG) works with OLD shapes, no shape edits.
    Circle{2.0, svg}.draw();
    Triangle{4.0, svg}.draw();

    std::cout << "\nComposition: 3 shapes plus 3 backends = 6 classes cover all\n"
                 "9 combinations. Adding a shape OR a backend is independent.\n"
                 "Growth is M plus N, not M times N - has-a trumps is-a.\n";
    return 0;
}
