/*
 * Guideline 33 - Be Aware of the Optimization Potential of Type Erasure
 *                (manual virtual dispatch instead of a Concept or Model pair)
 *
 * The second optimization from Guideline 33 targets the virtual functions that
 * the External Polymorphism design pattern introduces. A virtual call costs two
 * indirections: first through the per-object vptr to find the type's virtual
 * function table, then through the table to reach the actual function. We can cut
 * that to a single indirection by implementing the dispatch table ourselves:
 * store the function pointers directly inside the wrapper. We trade a little
 * space (a few extra pointers per wrapper) for speed.
 *
 * Because every virtual function is replaced, even the virtual destructor, there
 * is no need for a Concept base class anymore. The external hierarchy collapses
 * to a single OwningModel template that is merely storage for a ShapeT and a
 * DrawStrategy. The behavior lives in stateless lambdas created inside the
 * templated constructor, where the concrete types are still known. A stateless
 * lambda converts implicitly to a plain function pointer, so each lambda becomes
 * one entry of our hand-rolled dispatch table. Inside each lambda a static_cast
 * from void pointer back to the known OwningModel type is perfectly type safe:
 * the lambda was generated for exactly that model.
 *
 * Key notes:
 *   - One indirection instead of two: a direct function-pointer call rather than
 *     vptr then vtable. The Concept base and its virtual functions are gone.
 *   - The destroy operation is reused as the deleter of a unique_ptr<void, ...>,
 *     so cleanup runs the right destructor without any virtual machinery.
 *   - Stateless lambdas decay to function pointers; the static_cast back to the
 *     real OwningModel type inside each lambda is safe by construction.
 *   - Cost: the wrapper stores the dispatch table (extra pointers) per object,
 *     and copy operations must be written by hand (clone plus a copied table).
 */
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <new>
#include <utility>

// --- Tiny instrumented allocator so heap traffic is visible ---------------
namespace instrumented {
    inline std::size_t allocations = 0;
}

void* operator new(std::size_t n)
{
    instrumented::allocations += 1;
    if (n == 0) { n = 1; }
    void* p = std::malloc(n);
    if (p == nullptr) { throw std::bad_alloc(); }
    return p;
}

void operator delete(void* p) noexcept { std::free(p); }
void operator delete(void* p, std::size_t) noexcept { std::free(p); }

// --- Value-type shapes and stateless drawing strategies -------------------
struct Circle { double radius{}; };
struct Square { double side{}; };

struct DrawCircle { void operator()(const Circle& c) const { std::cout << "  [draw] circle r=" << c.radius << '\n'; } };
struct DrawSquare { void operator()(const Square& s) const { std::cout << "  [draw] square s=" << s.side << '\n'; } };

// --- Type Erasure wrapper with a hand-built dispatch table -----------------
class Shape
{
public:
    template <typename ShapeT, typename DrawStrategy>
    Shape(ShapeT shape, DrawStrategy drawer)
        : pimpl_(
              new OwningModel<ShapeT, DrawStrategy>(std::move(shape), std::move(drawer)),
              [](void* bytes) // destroy operation, used as the deleter
              {
                  using Model = OwningModel<ShapeT, DrawStrategy>;
                  delete static_cast<Model*>(bytes);
              })
        , draw_(
              [](void* bytes) // draw operation
              {
                  using Model = OwningModel<ShapeT, DrawStrategy>;
                  auto* const model = static_cast<Model*>(bytes);
                  model->drawer_(model->shape_);
              })
        , clone_(
              [](void* bytes) -> void* // clone operation
              {
                  using Model = OwningModel<ShapeT, DrawStrategy>;
                  auto* const model = static_cast<Model*>(bytes);
                  return new Model(*model);
              })
    {
    }

    Shape(const Shape& other)
        : pimpl_(other.clone_(other.pimpl_.get()), other.pimpl_.get_deleter())
        , draw_(other.draw_)
        , clone_(other.clone_)
    {
    }

    Shape& operator=(const Shape& other)
    {
        using std::swap; // copy and swap
        Shape copy(other);
        swap(pimpl_, copy.pimpl_);
        swap(draw_, copy.draw_);
        swap(clone_, copy.clone_);
        return *this;
    }

    ~Shape() = default;
    Shape(Shape&&) = default;
    Shape& operator=(Shape&&) = default;

    void draw() const { draw_(pimpl_.get()); }

private:
    // No Concept base: just storage. All behavior lives in the table below.
    template <typename ShapeT, typename DrawStrategy>
    struct OwningModel
    {
        OwningModel(ShapeT shape, DrawStrategy drawer)
            : shape_(std::move(shape)), drawer_(std::move(drawer))
        {
        }

        ShapeT shape_;
        DrawStrategy drawer_;
    };

    // The hand-built dispatch table: plain function-pointer types.
    using DestroyOperation = void(void*);
    using DrawOperation = void(void*);
    using CloneOperation = void*(void*);

    std::unique_ptr<void, DestroyOperation*> pimpl_; // owns model, knows destroy
    DrawOperation* draw_{nullptr};
    CloneOperation* clone_{nullptr};
};

int main()
{
    std::cout << "Manual virtual dispatch for a Type Erasure wrapper\n"
                 "sizeof(Shape) = " << sizeof(Shape)
              << " bytes (model pointer plus an inline dispatch table)\n\n";

    std::size_t before = instrumented::allocations;
    Shape circle{Circle{2.5}, DrawCircle{}};
    Shape square{Square{3.0}, DrawSquare{}};
    std::cout << "Built a circle and a square; heap allocations: "
              << (instrumented::allocations - before) << '\n';

    std::cout << "Drawing through the manual table (one indirection each):\n";
    circle.draw();
    square.draw();

    before = instrumented::allocations;
    Shape copy = circle; // uses the stored clone_ function pointer
    std::cout << "\nCopied the circle via the clone_ pointer; heap allocations: "
              << (instrumented::allocations - before) << '\n';
    copy.draw();

    Shape moved = std::move(square); // defaulted move just steals the unique_ptr
    std::cout << "Moved the square (no clone, pointer stolen):\n";
    moved.draw();

    std::cout << "\nTakeaway: replacing virtual functions with an explicit table of\n"
                 "function pointers removes one level of indirection per call and\n"
                 "drops the Concept base entirely; the cost is extra pointers per\n"
                 "wrapper and hand-written copy operations.\n";
    return 0;
}
