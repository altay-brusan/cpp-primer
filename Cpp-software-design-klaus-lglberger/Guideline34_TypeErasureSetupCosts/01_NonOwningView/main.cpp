/*
 * Guideline 34 - Be Aware of the Setup Costs of Owning Type Erasure Wrappers
 *                (owning value-semantic wrapper vs non-owning reference view)
 *
 * Guideline 32 builds an OWNING Type Erasure wrapper (Shape): it stores a copy
 * of the concrete shape plus its drawing strategy behind a unique_ptr. That
 * value-semantic design is beautiful, but the book warns it is not free. Every
 * time a Circle is converted into a Shape, the compiler creates a temporary via
 * the templated constructor, which COPIES the shape and the strategy and, inside
 * make_unique, performs a HEAP ALLOCATION. So using an owning wrapper merely as
 * a function parameter pays a copy plus an allocation on every call - the very
 * same trap std::function falls into, and the reason std::string_view and
 * std::span exist as cheap non-owning alternatives.
 *
 * When you only need to OPERATE on an object that already exists (typically to
 * hand it to a function), you do not need ownership. A NON-OWNING type-erased
 * view - the book's ShapeConstRef - stores just a pointer to the shape, a
 * pointer to the strategy, and a function pointer that performs the manually
 * implemented virtual dispatch (see Guideline 33). No copy, no allocation: it is
 * trivially copyable, exactly like string_view or span.
 *
 * This program contrasts the two. A global allocation counter proves the owning
 * wrapper allocates while the non-owning view does not, and a small chrono
 * timing shows the setup-cost gap. Circle and Square live on the stack and are
 * drawn through both wrappers.
 *
 * SAFETY: a non-owning view must NOT outlive the object it points to. We never
 * store a ShapeConstRef beyond the scope of the shape and strategy it refers to,
 * and the constructor takes lvalue references so temporaries (rvalues) cannot
 * bind to it - reasonable protection against dangling, per the book.
 *
 * Key notes:
 *   - Owning wrapper setup = copy of the erased object PLUS one heap allocation.
 *   - Non-owning view setup = a few pointer stores; zero allocation, zero copy.
 *   - Non-owning Type Erasure trades value semantics for reference semantics:
 *     great for function arguments, unsafe for data members or return types.
 *   - Prefer the simple non-owning form for parameters; reach for owning only
 *     when you truly need to store or return the abstraction.
 */
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <new>
#include <utility>

// --------------------------------------------------------------------------
// A tiny global heap-allocation counter so we can SEE the setup costs.
// Overloading the global new and delete is standard-library-only and lets us
// count every dynamic allocation the program makes.
// --------------------------------------------------------------------------
namespace {
std::size_t g_allocCount = 0;
std::size_t g_allocBytes = 0;
} // namespace

void* operator new(std::size_t n)
{
    ++g_allocCount;
    g_allocBytes += n;
    if (void* p = std::malloc(n == 0 ? 1 : n))
        return p;
    throw std::bad_alloc{};
}

void operator delete(void* p) noexcept { std::free(p); }
void operator delete(void* p, std::size_t) noexcept { std::free(p); }

// --------------------------------------------------------------------------
// Concrete, nonpolymorphic geometric primitives. They know nothing about
// drawing or about any wrapper - exactly the decoupling Type Erasure buys us.
// --------------------------------------------------------------------------
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

// ==========================================================================
// OWNING Type Erasure wrapper (the Guideline 32 style).
// It OWNS a copy of the shape and the strategy behind a unique_ptr, so every
// construction copies the erased object and allocates on the heap. This is the
// value-semantic design whose setup cost this guideline warns about.
// ==========================================================================
class Shape
{
public:
    // Templated constructor: converts ANY shape plus strategy into a Shape.
    // The copy of 'shape' and 'drawer' and the make_unique allocation happen
    // right here - this is the expensive setup.
    template <typename ShapeT, typename DrawStrategy>
    Shape(ShapeT shape, DrawStrategy drawer)
        : pimpl_(std::make_unique<Model<ShapeT, DrawStrategy>>(
              std::move(shape), std::move(drawer)))
    {
    }

    // Deep copy via clone: another allocation. Value semantics in action.
    Shape(const Shape& other) : pimpl_(other.pimpl_->clone()) {}
    Shape& operator=(const Shape& other)
    {
        Shape copy(other);
        pimpl_.swap(copy.pimpl_);
        return *this;
    }
    Shape(Shape&&) noexcept = default;
    Shape& operator=(Shape&&) noexcept = default;
    ~Shape() = default;

private:
    struct Concept
    {
        virtual ~Concept() = default;
        virtual void doDraw() const = 0;
        virtual std::unique_ptr<Concept> clone() const = 0;
    };

    template <typename ShapeT, typename DrawStrategy>
    struct Model final : Concept
    {
        Model(ShapeT shape, DrawStrategy drawer)
            : shape_(std::move(shape)), drawer_(std::move(drawer))
        {
        }
        void doDraw() const override { drawer_(shape_); }
        std::unique_ptr<Concept> clone() const override
        {
            return std::make_unique<Model>(*this);
        }
        ShapeT shape_;
        DrawStrategy drawer_;
    };

    friend void draw(const Shape& shape) { shape.pimpl_->doDraw(); }

    std::unique_ptr<Concept> pimpl_;
};

// ==========================================================================
// NON-OWNING Type Erasure view (the book's ShapeConstRef).
// It stores ONLY pointers: one to the existing shape, one to the existing
// strategy, and a function pointer that performs the manual virtual dispatch.
// No allocation, no copy of the erased object - trivially copyable like span.
//
// The constructor takes lvalue references, so rvalues (temporaries) cannot
// bind: that prevents the most obvious dangling-reference mistakes. Still, the
// view must not outlive the shape and strategy it points to.
// ==========================================================================
class ShapeConstRef
{
public:
    template <typename ShapeT, typename DrawStrategy>
    ShapeConstRef(ShapeT& shape, DrawStrategy& drawer)
        : shape_(std::addressof(shape))
        , drawer_(std::addressof(drawer))
        , draw_([](const void* shapeBytes, const void* drawerBytes) {
            const auto* s = static_cast<const ShapeT*>(shapeBytes);
            const auto* d = static_cast<const DrawStrategy*>(drawerBytes);
            (*d)(*s);
        })
    {
    }

private:
    friend void draw(const ShapeConstRef& shape)
    {
        shape.draw_(shape.shape_, shape.drawer_);
    }

    using DrawOperation = void(const void*, const void*);

    const void* shape_{nullptr};
    const void* drawer_{nullptr};
    DrawOperation* draw_{nullptr};
};

// A function that only needs to OPERATE on a shape briefly. Taking it by a
// non-owning view means the caller pays no allocation just to call us.
void useShapeConstRef(ShapeConstRef shape)
{
    draw(shape);
}

int main()
{
    std::cout << "Guideline 34: setup costs of owning vs non-owning wrappers\n";
    std::cout << "==========================================================\n\n";

    // Shapes and strategies live on the stack - they already exist.
    const Circle circle{3.14};
    const Square square{2.0};
    auto circleDrawer = [](const Circle& c) {
        std::cout << "  circle  r=" << c.radius() << '\n';
    };
    auto squareDrawer = [](const Square& s) {
        std::cout << "  square  s=" << s.side() << '\n';
    };

    // ---- Owning wrapper: measure allocations during construction. ----------
    const std::size_t before1 = g_allocCount;
    Shape owned{circle, circleDrawer};
    const std::size_t ownedAllocs = g_allocCount - before1;

    std::cout << "Owning Shape construction:\n";
    draw(owned);
    std::cout << "  -> heap allocations to set up: " << ownedAllocs << "\n\n";

    // ---- Non-owning view: measure allocations during construction. ---------
    const std::size_t before2 = g_allocCount;
    ShapeConstRef view{circle, circleDrawer};
    const std::size_t viewAllocs = g_allocCount - before2;

    std::cout << "Non-owning ShapeConstRef construction:\n";
    draw(view);
    std::cout << "  -> heap allocations to set up: " << viewAllocs << "\n\n";

    // The view works for any shape type, passed straight to a function with no
    // allocation - the cheap, span-like usage this guideline recommends.
    std::cout << "Passing stack objects through a non-owning parameter:\n";
    {
        ShapeConstRef sqView{square, squareDrawer};
        useShapeConstRef(sqView);
    }
    std::cout << '\n';

    // ---- A small timing and allocation comparison over many setups. --------
    constexpr int N = 100000;
    using clock = std::chrono::steady_clock;
    std::uintptr_t sink = 0; // keep the loops from being optimized away

    const std::size_t allocStartOwning = g_allocCount;
    const auto t0 = clock::now();
    for (int i = 0; i < N; ++i)
    {
        Shape s{circle, circleDrawer};
        sink += reinterpret_cast<std::uintptr_t>(&s);
    }
    const auto t1 = clock::now();
    const std::size_t owningLoopAllocs = g_allocCount - allocStartOwning;

    const std::size_t allocStartView = g_allocCount;
    const auto t2 = clock::now();
    for (int i = 0; i < N; ++i)
    {
        ShapeConstRef v{circle, circleDrawer};
        sink += reinterpret_cast<std::uintptr_t>(&v);
    }
    const auto t3 = clock::now();
    const std::size_t viewLoopAllocs = g_allocCount - allocStartView;

    const auto owningUs =
        std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count();
    const auto viewUs =
        std::chrono::duration_cast<std::chrono::microseconds>(t3 - t2).count();

    std::cout << "Setting up " << N << " wrappers each:\n";
    std::cout << "  owning  Shape        : " << owningUs << " us, "
              << owningLoopAllocs << " allocations\n";
    std::cout << "  non-owning ShapeConstRef: " << viewUs << " us, "
              << viewLoopAllocs << " allocations\n\n";

    std::cout << "Takeaway: the owning wrapper copies and allocates on every\n"
                 "setup; the non-owning view only stores pointers. Use the view\n"
                 "for function arguments, the owning wrapper for storage.\n";

    // Touch 'sink' so the optimizer must keep the measured loops.
    if (sink == 0)
        std::cout << "(unreachable sink guard)\n";

    return EXIT_SUCCESS;
}
