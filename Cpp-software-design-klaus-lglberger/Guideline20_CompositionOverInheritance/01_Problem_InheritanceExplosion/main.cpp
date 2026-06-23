/*
 * Guideline 20 - Favor Composition over Inheritance (the inheritance explosion)
 *
 * Two things vary here independently: WHAT we draw (Circle, Square) and HOW we
 * draw it (a Console backend, an OpenGL backend). This naive design models BOTH
 * dimensions with inheritance, fusing one shape together with one backend into
 * every leaf class: CircleConsole, CircleOpenGL, SquareConsole, SquareOpenGL.
 * The program compiles and runs, but the structure does not scale. As the book
 * warns, inheritance is the strongest, most rigid coupling, and it is overused;
 * here it forces a class for every combination instead of letting the two
 * dimensions vary on their own.
 *
 * Key notes:
 *   - The count is multiplicative: 2 shapes by 2 backends is 4 leaf classes.
 *     Add a Triangle and it becomes 6; add an SVG backend and it becomes 9.
 *     The growth is M times N, not M plus N.
 *   - Behavior is duplicated. The Console formatting is copied into both
 *     CircleConsole and SquareConsole; the radius is re-declared in each Circle
 *     variant. Inheritance did not give us reuse, it gave us copies.
 *   - The dimensions are tangled. You cannot add a backend without touching
 *     every shape, and you cannot add a shape without touching every backend.
 *   - This file is the BEFORE picture: it works, yet every new shape or backend
 *     multiplies the hierarchy. Composition (sample 02) breaks the multiply.
 */
#include <iostream>
#include <string>

// A common interface so the leaf classes can be used polymorphically.
class Shape
{
public:
    virtual ~Shape() = default;
    virtual void draw() const = 0;
};

// One class per (shape, backend) pair. The backend choice is baked in.
class CircleConsole : public Shape
{
public:
    explicit CircleConsole(double radius) : m_radius(radius) {}
    void draw() const override
    {
        // Console formatting - duplicated again in SquareConsole below.
        std::cout << "Console: Circle r=" << static_cast<int>(m_radius) << '\n';
    }

private:
    double m_radius;
};

class CircleOpenGL : public Shape
{
public:
    explicit CircleOpenGL(double radius) : m_radius(radius) {}
    void draw() const override
    {
        // OpenGL formatting - duplicated again in SquareOpenGL below.
        std::cout << "OpenGL: glDrawCircle(r=" << static_cast<int>(m_radius) << ")\n";
    }

private:
    double m_radius; // The same radius member, re-declared per variant.
};

class SquareConsole : public Shape
{
public:
    explicit SquareConsole(double side) : m_side(side) {}
    void draw() const override
    {
        std::cout << "Console: Square s=" << static_cast<int>(m_side) << '\n';
    }

private:
    double m_side;
};

class SquareOpenGL : public Shape
{
public:
    explicit SquareOpenGL(double side) : m_side(side) {}
    void draw() const override
    {
        std::cout << "OpenGL: glDrawSquare(s=" << static_cast<int>(m_side) << ")\n";
    }

private:
    double m_side;
};

int main()
{
    // Every combination needs its own dedicated type.
    CircleConsole circleOnConsole{2.0};
    CircleOpenGL  circleOnOpenGL{2.0};
    SquareConsole squareOnConsole{3.0};
    SquareOpenGL  squareOnOpenGL{3.0};

    std::cout << "Inheritance for both dimensions (one class per combination):\n";
    circleOnConsole.draw();
    circleOnOpenGL.draw();
    squareOnConsole.draw();
    squareOnOpenGL.draw();

    std::cout << "\nProblem: 2 shapes by 2 backends already needs 4 leaf classes.\n"
                 "Adding a Triangle needs TriangleConsole AND TriangleOpenGL;\n"
                 "adding an SVG backend needs CircleSVG, SquareSVG, TriangleSVG.\n"
                 "The hierarchy grows as M times N. Inheritance is rarely the answer.\n";
    return 0;
}
