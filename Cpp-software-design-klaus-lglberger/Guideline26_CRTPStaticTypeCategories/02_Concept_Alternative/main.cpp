/*
 * Guideline 26 - Use CRTP to Introduce Static Type Categories
 *                (the C++20 CONCEPT alternative the book recommends)
 *
 * The book closes Guideline 26 by noting that, with C++20, a concept often
 * SUPERSEDES this use of CRTP. A concept expresses the same static type category
 * - a family of types that provide a common interface - but NON-intrusively: a
 * type need not derive from anything to belong. If you can define the set of
 * types with a concept, the book says, prefer the concept over CRTP.
 *
 * One subtlety the book raises: a purely STRUCTURAL concept (just "has size and
 * subscript") is not specific enough. std::vector and std::string would slip in,
 * because they happen to provide the same operations. The remedy is to refine
 * the concept with an explicit OPT-IN. We do it via a customizable type trait,
 * IsDenseVector, so a type can join the category in TWO ways:
 *   - intrusively, by deriving (privately) from the DenseVectorTag marker, or
 *   - non-intrusively, by SPECIALIZING IsDenseVector to std::true_type.
 * The trait indirection applies the Single Responsibility Principle: structural
 * requirements and membership are separate concerns. In this form, as the book
 * puts it, the concept truly supersedes the classic CRTP approach.
 *
 * Key notes:
 *   - The concept IS the static type category - no base class, no static_cast,
 *     no template-of-self. Free functions are constrained on the concept.
 *   - Non-intrusive membership: StaticVector joins by a trait specialization,
 *     WITHOUT editing StaticVector. CRTP cannot do this for foreign types.
 *   - Intrusive membership still available: DynamicVector derives privately from
 *     the tag. std::is_base_of detects it even though the base is private.
 *   - Specificity via opt-in: std::vector satisfies the STRUCTURAL part but is
 *     NOT in the category, because it neither carries the tag nor specializes
 *     the trait. The static_asserts below prove it.
 *   - Trade-off vs CRTP: a concept gives no SHARED IMPLEMENTATION. CRTP could
 *     put common code in the base; with a concept each type implements its own.
 */
#include <array>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <iostream>
#include <type_traits>
#include <vector>

// The opt-in marker for intrusive membership.
struct DenseVectorTag {};

// Customizable membership trait. Default: a type belongs if it derives from the
// tag (is_base_of sees even a private base). Specialize it to opt in a type
// non-intrusively, without touching the type itself.
template <typename T>
struct IsDenseVector : std::is_base_of<DenseVectorTag, T> {};

template <typename T>
inline constexpr bool IsDenseVector_v = IsDenseVector<T>::value;

// The static type category, expressed as a concept: a STRUCTURAL part (the
// expected interface) refined by the membership trait (the explicit opt-in).
template <typename T>
concept DenseVector =
    requires(const T t, std::size_t i) {
        { t.size() } -> std::convertible_to<std::size_t>;
        t[i];
    } &&
    IsDenseVector_v<T>;

// Intrusive member: opts in by privately deriving from the tag. No CRTP, no
// self-as-template-argument - just a marker base.
template <typename T>
class DynamicVector : private DenseVectorTag
{
public:
    using value_type = T;

    DynamicVector(std::initializer_list<T> init) : m_values(init) {}

    std::size_t size() const { return m_values.size(); }
    T& operator[](std::size_t i) { return m_values[i]; }
    const T& operator[](std::size_t i) const { return m_values[i]; }

private:
    std::vector<T> m_values;
};

// A type that carries NO tag. We will opt it in non-intrusively below.
template <typename T, std::size_t Size>
class StaticVector
{
public:
    using value_type = T;

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

private:
    std::array<T, Size> m_values{};
};

// Non-intrusive opt-in: specialize the trait. StaticVector now belongs to the
// category without a single edit to its definition - the key win over CRTP.
template <typename T, std::size_t Size>
struct IsDenseVector<StaticVector<T, Size>> : std::true_type {};

// Free functions constrained on the concept. They accept any member of the
// category and reject look-alikes such as std::vector and std::string.
template <DenseVector V>
std::ostream& operator<<(std::ostream& os, const V& vec)
{
    os << "(";
    for (std::size_t i = 0; i < vec.size(); ++i)
        os << " " << vec[i];
    os << " )";
    return os;
}

template <DenseVector V>
double l2norm(const V& vec)
{
    double sum = 0.0;
    for (std::size_t i = 0; i < vec.size(); ++i)
    {
        const double v = static_cast<double>(vec[i]);
        sum += v * v;
    }
    return std::sqrt(sum);
}

int main()
{
    std::cout << "C++20 concept as the static type category (no CRTP):\n\n";

    DynamicVector<double> dyn{1.0, 2.0, 2.0};   // member via the tag
    StaticVector<double, 3> sta{3.0, 0.0, 4.0}; // member via trait specialization

    std::cout << "DynamicVector " << dyn << "  l2norm=" << l2norm(dyn) << "\n";
    std::cout << "StaticVector  " << sta << "  l2norm=" << l2norm(sta) << "\n\n";

    // Membership is precise: only types that opt in belong, even though others
    // share the same structural interface.
    static_assert(DenseVector<DynamicVector<double>>, "tagged type must belong");
    static_assert(DenseVector<StaticVector<double, 3>>, "specialized type must belong");
    static_assert(!DenseVector<std::vector<double>>,
                  "std::vector has the interface but did NOT opt in");
    static_assert(!DenseVector<int>, "int lacks the interface entirely");

    std::cout << "The concept defines the same category as the CRTP base, but\n"
                 "non-intrusively: a type joins by carrying the tag OR by a trait\n"
                 "specialization. std::vector is rejected despite matching the\n"
                 "interface, because it never opted in. Per the book, prefer the\n"
                 "concept to CRTP when a static category is all you need.\n";
    return 0;
}
