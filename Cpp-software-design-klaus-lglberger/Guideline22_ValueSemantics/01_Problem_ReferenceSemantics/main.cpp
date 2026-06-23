/*
 * Guideline 22 - Prefer Value Semantics over Reference Semantics
 *                (the reference-semantics design: pointers, aliasing, lifetime)
 *
 * This is the BEFORE picture from the book's argument. The classic GoF style
 * leans on inheritance hierarchies and therefore on pointers and references:
 * pointer-to-base polymorphism, non-owning observers, shared mutable state.
 * The book calls this reference semantics (or pointer semantics) because the
 * code works primarily through pointers and references. It compiles and runs,
 * but it forces us to reason by hand about questions value semantics never
 * raises: Who owns this object? Is this pointer valid or null? Does writing
 * here secretly change something over there? Is the referenced object still
 * alive?
 *
 * Every hazard below is shown in a controlled, safe way. The genuinely
 * undefined-behavior cases (reallocation and destruction while a non-owning
 * handle still points into the freed storage) are described in comments only
 * and are never executed.
 *
 * Key notes:
 *   - Pointer-to-base polymorphism means heap allocation, virtual dispatch,
 *     and a vector of pointers instead of a vector of values.
 *   - Raw observers (Shape pointers) are non-owning. The reader must remember
 *     who owns and must null-check before every use.
 *   - Shared mutable state aliases: two handles to one object, so a write
 *     through one is silently visible through the other. Surprising at a glance.
 *   - Reference types ignore const-ness of the value: a const std::span still
 *     lets you mutate the underlying array, because const binds the handle, not
 *     the pointed-to data.
 *   - Lifetime is a manual obligation: a reallocation or a clear() leaves every
 *     non-owning handle dangling. Shown only as a comment to avoid real UB.
 */
#include <iostream>
#include <memory>
#include <span>
#include <vector>

constexpr double kPi = 3.141592653589793;

// A polymorphic base: the moment we want this, we are in pointer land.
class Shape
{
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;
    virtual void describe() const = 0;
};

class Circle : public Shape
{
public:
    explicit Circle(double r) : m_r(r) {}
    double area() const override { return kPi * m_r * m_r; }
    void describe() const override { std::cout << "circle r=" << m_r << '\n'; }
    void setRadius(double r) { m_r = r; }

private:
    double m_r;
};

class Square : public Shape
{
public:
    explicit Square(double s) : m_s(s) {}
    double area() const override { return m_s * m_s; }
    void describe() const override { std::cout << "square s=" << m_s << '\n'; }

private:
    double m_s;
};

int main()
{
    // 1) Pointer-to-base polymorphism: heap allocations and virtual dispatch.
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(2.0));
    shapes.push_back(std::make_unique<Square>(3.0));

    std::cout << "Owned shapes (each on the heap, reached via a pointer):\n";
    for (const auto& sh : shapes)
        sh->describe();

    // 2) Non-owning observers. selection and alias point INTO shapes but own
    //    nothing. We must remember the ownership rule and must null-check.
    std::vector<Shape*> selection;
    selection.push_back(shapes[0].get());
    Shape* alias = shapes[0].get(); // a second handle to the SAME circle

    if (alias) // is it valid or null? reference semantics makes us ask
        alias->describe();

    // 3) Shared mutable state. Mutating through one alias is silently visible
    //    through every other alias, because they all name one object.
    if (auto* asCircle = dynamic_cast<Circle*>(selection[0]))
        asCircle->setRadius(10.0);

    std::cout << "\nAfter writing radius=10 through ONE alias:\n";
    std::cout << "  area via owner shapes[0]: " << shapes[0]->area() << '\n';
    std::cout << "  area via alias          : " << alias->area() << '\n';
    std::cout << "  (both changed - that is the aliasing surprise)\n";

    // 4) A reference type ignores the const-ness of the value it refers to.
    std::vector<int> v{1, 2, 3, 4};
    const std::vector<int> w{v};   // a real value copy: fully const, deep copy
    std::span<int> const view{v};  // a reference: const binds the handle only

    // w[2] = 99;   // would NOT compile: w is a value and is completely const
    view[2] = 99;    // compiles although view is const: it is a pointer in disguise

    std::cout << "\nconst handling differs for values vs references:\n";
    std::cout << "  w (a const value copy) still has w[2]=" << w[2] << '\n';
    std::cout << "  v mutated through a CONST span: v[2]=" << v[2] << '\n';

    // 5) Lifetime is a manual obligation (shown in comments, never executed):
    //      v.push_back(5);  may reallocate v, leaving view dangling  -> UB
    //      shapes.clear();  frees the circle, leaving alias and selection
    //                       pointing at freed storage                -> UB
    //    Value semantics simply does not pose any of these questions.
    std::cout << "\nReference semantics works, but every pointer raises a\n"
                 "question about ownership, validity, aliasing, and lifetime.\n";
    return 0;
}
