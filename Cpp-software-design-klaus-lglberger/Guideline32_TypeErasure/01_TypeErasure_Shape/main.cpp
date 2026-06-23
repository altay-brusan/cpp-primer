/*
 * Guideline 32 - Type Erasure: replace an inheritance hierarchy with a VALUE type
 *
 * Type Erasure is a COMPOUND design pattern. It fuses three patterns into one
 * regular, copyable value type (here Shape) that can hold ANY type that "looks
 * drawable" - without that type inheriting from anything or declaring a single
 * virtual function. It is the value-semantics finish of External Polymorphism.
 *
 * The three ingredients (see the book, Guideline 32):
 *
 *   - External Polymorphism : the abstract ShapeConcept and the templated
 *                             ShapeModel live OUTSIDE the concrete shapes, so
 *                             Circle and Square stay plain, nonpolymorphic
 *                             structs that never inherit and never go virtual.
 *   - Bridge                : the wrapper Shape owns a unique_ptr to the abstract
 *                             ShapeConcept (a pimpl). The concrete type hides
 *                             behind that pointer-to-base, and Shape itself has
 *                             no template parameter and no knowledge of T.
 *   - Prototype             : ShapeConcept exposes clone(), letting the wrapper
 *                             deep-copy whatever concrete object it owns without
 *                             knowing the type - the key to value semantics.
 *
 * Internal architecture, from the inside out:
 *
 *   ShapeConcept    abstract base. do_draw() plus clone() ARE the requirement
 *                   set every stored shape must satisfy. The names are our own
 *                   implementation detail and need not match anything on T.
 *   ShapeModel<T>   the one and only model. Derives from ShapeConcept, stores a
 *                   T by value, implements do_draw() by calling the free function
 *                   draw(const T) found through argument dependent lookup, and
 *                   implements clone() by copying itself into a fresh model.
 *   Shape           the public value type. Its templated constructor ERASES T:
 *                   it builds a ShapeModel<T> on the heap and keeps only a
 *                   unique_ptr<ShapeConcept>. After construction Shape has no
 *                   member, parameter, or function that reveals T - the concrete
 *                   type has been erased. Hence the name of the pattern.
 *
 * Once T is gone, Shape behaves like any other value: copy it (a deep copy via
 * clone()), move it, store it in a std::vector, pass it by value. The free
 * function draw(const Shape) forwards through the bridge to do_draw(). Adding a
 * new shape needs only a new struct plus a free draw() for it - no base class,
 * no edit to Shape, ShapeConcept, or ShapeModel. That is the payoff over an
 * inheritance hierarchy: strong decoupling AND value semantics.
 *
 * One hazard worth calling out: the templated constructor template<class T>
 * Shape(T) is greedy and could match Shape(const Shape) and hijack the copy
 * constructor. It is constrained with a requires-clause so it never applies when
 * T is Shape, which leaves the real copy constructor to win for Shape arguments.
 *
 * Key notes:
 *   - Type Erasure equals External Polymorphism plus Bridge plus Prototype, as a value.
 *   - Concrete shapes are plain structs: no base class, no virtual functions.
 *   - clone() in the Concept is what gives the wrapper deep-copy value semantics.
 *   - The concrete type lives only inside ShapeModel<T>; Shape forgets it (erased).
 *   - Constrain the templated ctor so it cannot steal the copy constructor.
 *   - Type Erasure shines for unary ops; binary ops (e.g. equality) are awkward.
 */
#include <concepts>
#include <iostream>
#include <memory>
#include <type_traits>
#include <utility>
#include <vector>

// ---- Concrete shapes: plain structs, NO base class, NO virtual functions ----

struct Circle
{
    double radius;
};

struct Square
{
    double side;
};

// Free drawing functions. Each concrete type supplies its own; they are picked
// up by argument dependent lookup from inside the model. The shapes themselves
// know nothing about drawing beyond the existence of these free functions, so
// the drawing behavior stays fully decoupled from the geometry.
void draw(const Circle& c)
{
    std::cout << "Circle(radius=" << c.radius << ")\n";
}

void draw(const Square& s)
{
    std::cout << "Square(side=" << s.side << ")\n";
}

// ---- The Type Erasure wrapper: a regular value type -------------------------

class Shape
{
public:
    // Templated constructor: ERASES the concrete type T. Constrained so it never
    // matches another Shape; otherwise it would hijack the copy constructor.
    template <class T>
        requires(!std::same_as<std::remove_cvref_t<T>, Shape>)
    Shape(T value)
        : pimpl_{ std::make_unique<ShapeModel<T>>(std::move(value)) }
    {
    }

    // Copy constructor: a real deep copy via the Prototype clone(). We never
    // learn the concrete type, yet we still duplicate it exactly.
    Shape(const Shape& other)
        : pimpl_{ other.pimpl_->clone() }
    {
    }

    // Copy assignment via the copy-and-swap idiom.
    Shape& operator=(const Shape& other)
    {
        Shape copy{ other };
        pimpl_.swap(copy.pimpl_);
        return *this;
    }

    // unique_ptr makes the destructor and the move operations correct for free.
    Shape(Shape&&) noexcept = default;
    Shape& operator=(Shape&&) noexcept = default;
    ~Shape() = default;

private:
    // External Polymorphism: the abstract requirement set lives OUTSIDE shapes.
    struct ShapeConcept
    {
        virtual ~ShapeConcept() = default;
        virtual void do_draw() const = 0;
        virtual std::unique_ptr<ShapeConcept> clone() const = 0;
    };

    // The single model template. Stores a T by value and forwards to free draw().
    template <class T>
    struct ShapeModel : ShapeConcept
    {
        explicit ShapeModel(T value)
            : object_{ std::move(value) }
        {
        }

        void do_draw() const override
        {
            draw(object_); // resolved by argument dependent lookup on T
        }

        std::unique_ptr<ShapeConcept> clone() const override
        {
            return std::make_unique<ShapeModel>(*this);
        }

        T object_;
    };

    // Bridge: a single pointer to the abstract base hides the erased type.
    std::unique_ptr<ShapeConcept> pimpl_;

    // Hidden friend: a free function (decoupled, like the per-type draws) that
    // still gets private access to forward through the bridge to do_draw().
    friend void draw(const Shape& shape)
    {
        shape.pimpl_->do_draw();
    }
};

int main()
{
    // Value semantics: a vector of plain VALUES, not pointers. Circle and Square
    // are unrelated structs with no common base, yet both fit inside Shape.
    std::vector<Shape> shapes;
    shapes.emplace_back(Circle{ 1.5 });
    shapes.emplace_back(Square{ 2.0 });
    shapes.push_back(Circle{ 3.25 });

    std::cout << "Original shapes:\n";
    for (const Shape& s : shapes)
        draw(s);

    // Copy the whole container BY VALUE. Each Shape deep-copies its hidden
    // concrete object through clone() - no shared pointers, no aliasing.
    std::vector<Shape> copies = shapes;

    // Reassign one element to a different concrete type, by value. The Square
    // converts to a temporary Shape (templated ctor), then move assignment runs.
    copies[0] = Square{ 9.0 };

    std::cout << "\nCopies after reassigning copies[0] to a Square:\n";
    for (const Shape& s : copies)
        draw(s);

    std::cout << "\nOriginals are untouched (deep copy, true value semantics):\n";
    for (const Shape& s : shapes)
        draw(s);

    return 0;
}
