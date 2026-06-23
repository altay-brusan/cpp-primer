/*
 * Guideline 7 - Understand the Similarities Between Base Classes and Concepts
 *               (the COMPILE-TIME abstraction: a C++20 concept)
 *
 * This sample expresses the SAME requirement as sample 01, but as static
 * (compile-time) polymorphism. Instead of a Document base class, we define a
 * C++20 concept named Document that lists the expected operations -
 * exportToJSON() and serialize(ByteStream&). useDocument() is a function
 * template constrained by that concept, so it accepts ANY type that satisfies
 * the concept, that is, any type that adheres to the expectations of the
 * Document abstraction. There is no inheritance and no vtable: the right
 * function is selected at COMPILE time.
 *
 * The book's central observation is that the base class and the concept are
 * semantically the same thing. Both represent a set of requirements (syntactic
 * AND semantic) and a formal description of expected behavior; both are the
 * means by which calling code communicates its expectations. The concept is the
 * static counterpart - the equivalent - of the base class. So the LSP applies
 * to templated code just as it does to inheritance hierarchies.
 *
 * Key notes:
 *   - A C++20 concept is a COMPILE-TIME abstraction. The requires-clause IS the
 *     set of expected operations, mirroring the base class's virtual functions.
 *   - PDF and Word do NOT inherit anything. They are unrelated value types that
 *     simply provide the required operations; the concept binds them at compile
 *     time. A type that lacks an operation fails to compile with a clear error.
 *   - No runtime cost: no vtable, no virtual dispatch. The trade-off is that the
 *     types must be known at compile time (no heterogeneous container of one
 *     static type), which sample 01's base class allows and this one does not.
 *   - Concepts cannot FULLY encode semantics, but they still express expected
 *     behavior; like a base class they are LSP abstractions, hence the duality.
 */
#include <concepts>
#include <iostream>
#include <string>
#include <string_view>

// Minimal stand-in for the book's ByteStream (standard library only).
class ByteStream
{
public:
    void writeTag(std::string_view tag) { m_buffer += "[tag="; m_buffer += tag; m_buffer += "]"; }
    void writeBody(std::string_view body) { m_buffer += body; }
    const std::string& str() const { return m_buffer; }

private:
    std::string m_buffer;
};

// The COMPILE-TIME abstraction: a concept whose requires-clause lists the same
// expected operations the base class declared as pure virtual functions.
template <typename T>
concept Document = requires(const T t, ByteStream& b)
{
    { t.exportToJSON() } -> std::convertible_to<std::string>;
    { t.serialize(b) };
};

// Two UNRELATED value types - no inheritance. Each simply provides the required
// operations, so each satisfies the Document concept.
struct PDF
{
    std::string exportToJSON() const { return R"({"format":"pdf"})"; }
    void serialize(ByteStream& bs) const { bs.writeTag("PDF"); bs.writeBody("PDF-content"); }
};

struct Word
{
    std::string exportToJSON() const { return R"({"format":"word"})"; }
    void serialize(ByteStream& bs) const { bs.writeTag("WORD"); bs.writeBody("Word-content"); }
};

// Constrained template: works with any type satisfying the abstraction. The
// concrete call is resolved at COMPILE time (static dispatch). Compare this to
// useDocument(Document const&) in sample 01 - same intent, different binding.
template <Document T>
void useDocument(const T& doc)
{
    ByteStream bs;
    doc.serialize(bs);
    std::cout << "  json=" << doc.exportToJSON() << "  bytes=" << bs.str() << '\n';
}

int main()
{
    std::cout << "Compile-time abstraction (C++20 concept + constrained template):\n";

    PDF pdf;
    Word word;
    useDocument(pdf);
    useDocument(word);

    // Proof that the concept is checked at compile time.
    static_assert(Document<PDF>, "PDF must satisfy the Document concept");
    static_assert(Document<Word>, "Word must satisfy the Document concept");
    static_assert(!Document<int>, "int does not satisfy the Document concept");

    std::cout << "\nThe concept is the abstraction: the requires-clause is the\n"
                 "same set of expected operations the base class declared. Binding\n"
                 "happens at compile time, with no vtable - the static counterpart\n"
                 "of sample 01's base class.\n";
    return 0;
}
