/*
 * Guideline 33 - Be Aware of the Optimization Potential of Type Erasure
 *                (Small Buffer Optimization for the Type Erasure wrapper)
 *
 * In Guideline 32 the Type Erasure wrapper unconditionally heap-allocated its
 * erased object inside the constructor and clone, independent of the object's
 * size. Acquiring and freeing dynamic memory is slow and nondeterministic, and
 * in some environments dynamic memory is not even available. Because we now own
 * a value type and a wrapper, not just a pointer to base, we are in full control
 * of memory. The Small Buffer Optimization (SBO) stores small erased objects
 * inline, in an aligned in-class byte buffer, and only falls back to the heap
 * for objects too large to fit. The standard library uses this same trick in
 * std::function and std::any.
 *
 * This wrapper keeps the External Polymorphism inheritance pair (a Concept base
 * and an OwningModel template) but instead of std::make_unique it constructs the
 * model in place. With in-class memory we become responsible for the model's
 * lifetime: construct via std::construct_at (placement new), copy and move via
 * clone and move into the destination buffer, and tear down via std::destroy_at,
 * which runs the virtual destructor. A small instrumented operator new proves
 * that small shapes trigger zero heap allocations while large ones fall back to
 * one allocation.
 *
 * Key notes:
 *   - SBO trades a fixed amount of space (the inline buffer) for speed: no heap
 *     traffic and no memory fragmentation for the common, small case.
 *   - The buffer is alignas(Alignment) so placement new into it is well defined;
 *     a compile-time check selects inline storage only when the model fits in
 *     Capacity and is not over-aligned, otherwise it goes on the heap.
 *   - Manual lifetime: construct_at builds in place, destroy_at runs the dtor;
 *     for inline objects there is no delete, only the destructor call.
 *   - Cost of SBO: the wrapper becomes a class template (Capacity, Alignment),
 *     so code using it tends to become templated too. That is the price of the
 *     in-class buffer.
 */
#include <array>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <new>
#include <utility>

// --- Tiny instrumented allocator so we can SEE heap traffic ---------------
// Only global operator new is counted; inline (in-class) construction never
// reaches it. We snapshot the counter around each operation in main.
namespace instrumented {
    inline std::size_t allocations = 0;
    inline std::size_t bytes = 0;
}

void* operator new(std::size_t n)
{
    instrumented::allocations += 1;
    instrumented::bytes += n;
    if (n == 0) { n = 1; }
    void* p = std::malloc(n);
    if (p == nullptr) { throw std::bad_alloc(); }
    return p;
}

void operator delete(void* p) noexcept { std::free(p); }
void operator delete(void* p, std::size_t) noexcept { std::free(p); }

// --- A couple of value-type shapes (the erased types) ---------------------
struct Circle { double radius{}; };
struct Square { double side{}; };

// A deliberately large shape so it cannot fit in the inline buffer.
struct BigShape
{
    double weight{};
    std::array<char, 64> blob{}; // pushes sizeof well past the buffer
};

// Drawing strategies (the HOW). Stateless functors stay tiny.
struct DrawCircle { void operator()(const Circle& c) const { std::cout << "  [draw] circle r=" << c.radius << '\n'; } };
struct DrawSquare { void operator()(const Square& s) const { std::cout << "  [draw] square s=" << s.side << '\n'; } };
struct DrawBig    { void operator()(const BigShape& b) const { std::cout << "  [draw] big shape w=" << b.weight << " (heap)\n"; } };

// --- The Type Erasure wrapper with Small Buffer Optimization --------------
template <std::size_t Capacity = 32U, std::size_t Alignment = alignof(std::max_align_t)>
class Shape
{
public:
    // Two-parameter templated constructor: erases ShapeT and DrawStrategy.
    // It has two parameters, so it never competes with the one-parameter copy
    // or move constructors below.
    template <typename ShapeT, typename DrawStrategy>
    Shape(ShapeT shape, DrawStrategy drawer)
    {
        using Model = OwningModel<ShapeT, DrawStrategy>;
        place<Model>(std::move(shape), std::move(drawer));
    }

    Shape(const Shape& other) { other.pimpl()->clone(*this); }

    Shape(Shape&& other) noexcept { takeFrom(std::move(other)); }

    Shape& operator=(const Shape& other)
    {
        if (this != &other)
        {
            destroy();
            other.pimpl()->clone(*this);
        }
        return *this;
    }

    Shape& operator=(Shape&& other) noexcept
    {
        if (this != &other)
        {
            destroy();
            takeFrom(std::move(other));
        }
        return *this;
    }

    ~Shape() { destroy(); }

    void draw() const { pimpl()->draw(); }

    // For the demo: did this object avoid the heap?
    bool isInline() const { return !onHeap_; }

private:
    // External Polymorphism: the abstraction and one model per erased type.
    struct Concept
    {
        virtual ~Concept() = default;
        virtual void draw() const = 0;
        // Copy or move THIS model into the destination wrapper's storage.
        virtual void clone(Shape& dest) const = 0;
        virtual void move(Shape& dest) = 0;
    };

    template <typename ShapeT, typename DrawStrategy>
    struct OwningModel : public Concept
    {
        OwningModel(ShapeT shape, DrawStrategy drawer)
            : shape_(std::move(shape)), drawer_(std::move(drawer))
        {
        }

        void draw() const override { drawer_(shape_); }

        // Re-run the same inline-or-heap decision in the destination.
        void clone(Shape& dest) const override { dest.place<OwningModel>(*this); }
        void move(Shape& dest) override { dest.place<OwningModel>(std::move(*this)); }

        ShapeT shape_;
        DrawStrategy drawer_;
    };

    // Construct a Model either inline (placement new into the buffer) or on the
    // heap, depending on whether it fits and is suitably aligned.
    template <typename Model, typename... Args>
    void place(Args&&... args)
    {
        if constexpr (sizeof(Model) <= Capacity && alignof(Model) <= Alignment)
        {
            pimpl_ = std::construct_at(
                reinterpret_cast<Model*>(buffer_.data()), std::forward<Args>(args)...);
            onHeap_ = false;
        }
        else
        {
            pimpl_ = new Model(std::forward<Args>(args)...);
            onHeap_ = true;
        }
    }

    // Steal from a moved-from wrapper: pointers can be stolen for heap storage,
    // but inline storage must be move-constructed element by element.
    void takeFrom(Shape&& other)
    {
        if (other.onHeap_)
        {
            pimpl_ = other.pimpl_;
            onHeap_ = true;
        }
        else if (other.pimpl_ != nullptr)
        {
            other.pimpl_->move(*this);      // build a moved copy inline in *this
            std::destroy_at(other.pimpl_);  // tear down the husk left behind
        }
        other.pimpl_ = nullptr;
    }

    void destroy() noexcept
    {
        if (pimpl_ == nullptr) { return; }
        if (onHeap_) { delete pimpl_; }          // virtual dtor plus free
        else { std::destroy_at(pimpl_); }        // virtual dtor only
        pimpl_ = nullptr;
    }

    Concept* pimpl() { return pimpl_; }
    const Concept* pimpl() const { return pimpl_; }

    alignas(Alignment) std::array<std::byte, Capacity> buffer_{};
    Concept* pimpl_{nullptr};
    bool onHeap_{false};
};

// --- Demonstration --------------------------------------------------------
namespace {
    std::size_t snapshot() { return instrumented::allocations; }

    void report(const char* what, std::size_t before)
    {
        std::cout << "  -> heap allocations for " << what << ": "
                  << (instrumented::allocations - before) << '\n';
    }
}

int main()
{
    using SmallShape = Shape<>; // default 32-byte buffer

    std::cout << "Small Buffer Optimization for a Type Erasure wrapper\n"
                 "sizeof(Shape<>) = " << sizeof(SmallShape) << " bytes\n\n";

    // Small shapes: expect ZERO heap allocations (stored inline).
    {
        std::size_t before = snapshot();
        SmallShape circle{Circle{2.5}, DrawCircle{}};
        SmallShape square{Square{3.0}, DrawSquare{}};
        std::size_t built = instrumented::allocations - before;

        std::cout << "Built one circle and one square (small):\n";
        std::cout << "  circle stored inline? " << std::boolalpha << circle.isInline() << '\n';
        std::cout << "  square stored inline? " << square.isInline() << '\n';
        std::cout << "  -> heap allocations while building both: " << built << '\n';
        circle.draw();
        square.draw();

        before = snapshot();
        SmallShape copy = circle; // clone, still inline
        std::cout << "Copied the circle:\n";
        std::cout << "  copy stored inline? " << copy.isInline() << '\n';
        report("the copy", before);
        copy.draw();
        std::cout << '\n';
    }

    // Large shape: does not fit the buffer, so it falls back to the heap.
    {
        std::size_t before = snapshot();
        SmallShape big{BigShape{42.0}, DrawBig{}};
        std::cout << "Built one BigShape (too large for the buffer):\n";
        std::cout << "  big stored inline? " << big.isInline() << '\n';
        report("the big shape", before);
        big.draw();

        before = snapshot();
        SmallShape bigCopy = big; // clone, allocates again
        std::cout << "Copied the BigShape:\n";
        report("the big copy", before);
        bigCopy.draw();
        std::cout << '\n';
    }

    std::cout << "Takeaway: small erased objects avoid the heap entirely; only\n"
                 "objects too large for the inline buffer fall back to dynamic\n"
                 "memory. The wrapper owns the model's lifetime in both cases.\n";
    return 0;
}
