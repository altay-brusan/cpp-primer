/*
 * Guideline 26 - Use CRTP to Introduce Static Type Categories
 *                (the Curiously Recurring Template Pattern as a COMPILE-TIME
 *                 abstraction for a family of related types)
 *
 * The book's motivation is a linear-algebra library with two vector classes,
 * DynamicVector (heap storage via std::vector) and StaticVector (in-class
 * std::array). They share an interface - size, subscript, begin, end - and
 * share free functions such as the output operator and l2norm. Pulling that
 * shared interface into a runtime base class with virtual functions would be a
 * disaster here: every element access would pay for a virtual call, and in
 * high-performance computing that overhead is unacceptable.
 *
 * CRTP keeps the abstraction but moves the relationship from RUNTIME to COMPILE
 * time. The base is a class template DenseVector<Derived>; each concrete vector
 * passes ITS OWN type as the template argument and derives from it. The base
 * forwards every call to the derived implementation with a static_cast to
 * Derived, so the family shares one static interface with NO virtual dispatch.
 * The cast is hidden behind a derived() helper; the base destructor is
 * protected and nonvirtual (Core Guideline C.35) because there is no runtime
 * polymorphism to support.
 *
 * Key notes:
 *   - Intent: define a compile-time abstraction for a family of related types.
 *     DenseVector<Derived> is the shared static interface; the static_cast in
 *     derived() typically inlines away to nothing.
 *   - There is NO common base class - DynamicVector and StaticVector each have a
 *     DIFFERENT base (DenseVector of themselves), so you cannot store them in
 *     one polymorphic container. CRTP buys static, not runtime, polymorphism.
 *   - Return types use decltype(auto): the base returns EXACTLY what the derived
 *     returns. ZeroVector returns elements BY VALUE, so a plain auto and ref
 *     would be wrong; decltype(auto) stays correct as the family grows.
 *   - The base cannot read nested types of Derived (it is still incomplete when
 *     the base is instantiated), but it CAN call Derived member functions:
 *     member functions of a class template are instantiated on demand, by which
 *     time Derived is complete. ZeroVector never calls begin, so the base begin
 *     is simply never instantiated for it - and that is fine.
 *   - Free functions over the category become TEMPLATES on Derived (see operator
 *     and l2norm below). That spread of template code is one of CRTP's costs.
 */
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <vector>

// The CRTP base: a compile-time abstraction for the dense-vector category.
// Derived is the concrete vector type, supplied by the derived class itself.
template <typename Derived>
struct DenseVector
{
protected:
    // Nonvirtual and protected: no runtime polymorphism, no deletion through a
    // DenseVector pointer. Adheres to Core Guideline C.35.
    ~DenseVector() = default;

public:
    // The single, contained cast. Everything else forwards through here.
    Derived& derived() { return static_cast<Derived&>(*this); }
    const Derived& derived() const { return static_cast<const Derived&>(*this); }

    std::size_t size() const { return derived().size(); }

    // decltype(auto): forward the derived return type verbatim (ref or value).
    decltype(auto) operator[](std::size_t index) { return derived()[index]; }
    decltype(auto) operator[](std::size_t index) const { return derived()[index]; }

    decltype(auto) begin() { return derived().begin(); }
    decltype(auto) begin() const { return derived().begin(); }
    decltype(auto) end() { return derived().end(); }
    decltype(auto) end() const { return derived().end(); }
};

// A concrete dense vector with dynamic (heap) storage. It passes its own type to
// the base - a curiously recurring use of the type being defined.
template <typename T>
class DynamicVector : public DenseVector<DynamicVector<T>>
{
public:
    using value_type = T;
    using const_iterator = typename std::vector<T>::const_iterator;

    DynamicVector(std::initializer_list<T> init) : m_values(init) {}

    std::size_t size() const { return m_values.size(); }

    T& operator[](std::size_t i) { return m_values[i]; }
    const T& operator[](std::size_t i) const { return m_values[i]; }

    typename std::vector<T>::iterator begin() { return m_values.begin(); }
    const_iterator begin() const { return m_values.begin(); }
    typename std::vector<T>::iterator end() { return m_values.end(); }
    const_iterator end() const { return m_values.end(); }

private:
    std::vector<T> m_values;
};

// A concrete dense vector with fixed in-class storage. Same static interface,
// different base instantiation - and no virtual calls in sight.
template <typename T, std::size_t Size>
class StaticVector : public DenseVector<StaticVector<T, Size>>
{
public:
    using value_type = T;
    using const_iterator = typename std::array<T, Size>::const_iterator;

    StaticVector(std::initializer_list<T> init)
    {
        std::size_t i = 0;
        for (const T& v : init)
        {
            if (i >= Size) break;
            m_values[i++] = v;
        }
    }

    std::size_t size() const { return Size; }

    T& operator[](std::size_t i) { return m_values[i]; }
    const T& operator[](std::size_t i) const { return m_values[i]; }

    typename std::array<T, Size>::iterator begin() { return m_values.begin(); }
    const_iterator begin() const { return m_values.begin(); }
    typename std::array<T, Size>::iterator end() { return m_values.end(); }
    const_iterator end() const { return m_values.end(); }

private:
    std::array<T, Size> m_values{};
};

// A dense vector that stores NOTHING and yields zero BY VALUE. This is why the
// base uses decltype(auto): an auto-ref return type would be wrong here.
template <typename T>
class ZeroVector : public DenseVector<ZeroVector<T>>
{
public:
    using value_type = T;

    explicit ZeroVector(std::size_t n) : m_size(n) {}

    std::size_t size() const { return m_size; }

    // Returns by value - there is no element to bind a reference to.
    T operator[](std::size_t) const { return T{}; }

private:
    std::size_t m_size;
};

// Free functions over the WHOLE category. They take the base by reference and
// must be templates on Derived - a cost of CRTP, but they then work for every
// dense vector, present and future, with no virtual call.
template <typename Derived>
std::ostream& operator<<(std::ostream& os, const DenseVector<Derived>& vec)
{
    os << "(";
    for (std::size_t i = 0; i < vec.size(); ++i)
        os << " " << vec[i];
    os << " )";
    return os;
}

template <typename Derived>
double l2norm(const DenseVector<Derived>& vec)
{
    double sum = 0.0;
    for (std::size_t i = 0; i < vec.size(); ++i)
    {
        const double v = static_cast<double>(vec[i]);
        sum += v * v;
    }
    return std::sqrt(sum);
}

// Demonstrates iterator forwarding THROUGH the base interface: begin and end on
// a DenseVector reference forward to the derived iterators. ZeroVector never
// reaches this function, so its missing begin is never instantiated.
template <typename Derived>
void printViaIterators(const DenseVector<Derived>& vec)
{
    std::cout << "  via base iterators:";
    for (auto it = vec.begin(); it != vec.end(); ++it)
        std::cout << " " << *it;
    std::cout << "\n";
}

int main()
{
    std::cout << "CRTP static type category - one interface, no virtual calls:\n\n";

    DynamicVector<double> dyn{1.0, 2.0, 2.0};
    StaticVector<double, 3> sta{3.0, 0.0, 4.0};
    ZeroVector<double> zero{4};

    // The same free operator and l2norm serve every member of the category.
    std::cout << "DynamicVector " << dyn << "  l2norm=" << l2norm(dyn) << "\n";
    std::cout << "StaticVector  " << sta << "  l2norm=" << l2norm(sta) << "\n";
    std::cout << "ZeroVector    " << zero << "  l2norm=" << l2norm(zero) << "\n\n";

    // Iterator forwarding works for the storage-backed vectors.
    printViaIterators(dyn);
    printViaIterators(sta);

    std::cout << "\nThe base forwards every call to the derived type with a\n"
                 "static_cast, so the dense-vector family shares one static\n"
                 "interface at compile time - and pays nothing for virtual\n"
                 "dispatch. Note there is NO common base: dyn and sta have\n"
                 "different DenseVector instantiations and cannot share a\n"
                 "polymorphic container.\n";
    return 0;
}
