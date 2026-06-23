/*
 * Guideline 19 - Use Strategy to Isolate How Things Are Done
 *                (the inheritance trap: baking HOW into the type)
 *
 * The book's 2D graphics example. A Shape base class offers a pure virtual
 * draw(), and the team implements draw() right inside each shape. As soon as a
 * second drawing backend is needed (say OpenGL versus a plain console), they
 * reach for inheritance: an OpenGLCircle, a ConsoleCircle, an OpenGLSquare, a
 * ConsoleSquare, and so on. This compiles and runs, but it bakes the HOW (the
 * drawing detail) into the WHAT (the geometric type), violating the Single
 * Responsibility Principle. The number of classes then explodes along every
 * new axis of variation.
 *
 * Key notes:
 *   - Drawing is a variation point, yet here it lives inside the shape type.
 *     Circle now depends on its rendering backend, so a shape cannot be a simple
 *     geometric primitive anymore.
 *   - Adding a backend means a new subclass per shape: with 2 shapes and 2
 *     backends you already have 4 leaf classes. Add a Metal backend and it is 6.
 *     The grid grows as shapes times backends.
 *   - Add a second varying operation (the book uses serialize) and the hierarchy
 *     multiplies again: OpenGLProtobufCircle, MetalBoostSquare, and the like.
 *     Inheritance is rarely the answer.
 *   - You cannot change a single shape instance's drawing at runtime, and you
 *     cannot reuse the OpenGL code between, say, a circle and a square.
 *   - This file is the BEFORE picture: it works, but it is closed against the
 *     kind of change the book predicts is coming.
 */
#include <iostream>

// A shape is meant to be a simple geometric primitive.
class Shape
{
public:
    virtual ~Shape() = default;
    virtual void draw() const = 0;
};

// Console backend baked into the types ------------------------------------

class ConsoleCircle : public Shape
{
public:
    explicit ConsoleCircle(double radius) : m_radius(radius) {}
    void draw() const override
    {
        std::cout << "[console] circle r=" << m_radius << '\n';
    }

private:
    double m_radius;
};

class ConsoleSquare : public Shape
{
public:
    explicit ConsoleSquare(double side) : m_side(side) {}
    void draw() const override
    {
        std::cout << "[console] square s=" << m_side << '\n';
    }

private:
    double m_side;
};

// A SECOND backend forces a whole new row of subclasses -------------------

class OpenGLCircle : public Shape
{
public:
    explicit OpenGLCircle(double radius) : m_radius(radius) {}
    void draw() const override
    {
        std::cout << "[opengl] circle r=" << m_radius << '\n';
    }

private:
    double m_radius;
};

class OpenGLSquare : public Shape
{
public:
    explicit OpenGLSquare(double side) : m_side(side) {}
    void draw() const override
    {
        std::cout << "[opengl] square s=" << m_side << '\n';
    }

private:
    double m_side;
};

// Adding a Metal backend would mean MetalCircle and MetalSquare too, and a
// serialize operation would multiply the whole grid again. The hierarchy
// grows as shapes times backends times operations.

int main()
{
    std::cout << "Inheritance baked the backend into the type:\n";

    ConsoleCircle cc{2.3};
    ConsoleSquare cs{1.2};
    OpenGLCircle  oc{4.1};
    OpenGLSquare  os{3.0};

    cc.draw();
    cs.draw();
    oc.draw();
    os.draw();

    std::cout << "\nProblem: every backend is a new subclass per shape, so the\n"
                 "class count grows as shapes times backends. A circle's drawing\n"
                 "cannot change at runtime, and the OpenGL code cannot be shared\n"
                 "between shapes. The HOW is welded to the WHAT.\n";
    return 0;
}
