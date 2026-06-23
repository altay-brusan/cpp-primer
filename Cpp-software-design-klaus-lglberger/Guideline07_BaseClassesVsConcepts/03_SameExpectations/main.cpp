/*
 * Guideline 7 - Understand the Similarities Between Base Classes and Concepts
 *               (two sides of the same coin: one type, both abstractions)
 *
 * Samples 01 and 02 showed the two styles separately. This sample drives the
 * book's punchline home: the base class and the concept describe the SAME set
 * of expectations, so a single concrete type can model BOTH at once. Here PDF
 * derives from the runtime Document base class AND also satisfies the
 * compile-time Document concept - the concept's requirements are literally the
 * base class's interface restated. We then call useDocument() in both styles
 * and observe identical behavior.
 *
 * This is exactly the "deja vu" the book points at: whether useDocument()
 * accepts a "Document const&" (runtime) or a constrained "Document T"
 * (compile-time), in both cases it works only with classes adhering to the
 * expectations of the Document abstraction. The two functions are very similar
 * from a semantic point of view; they differ only in WHEN the binding happens.
 *
 * Key notes:
 *   - One IS-A relationship, two encodings: the base class checks it at run
 *     time via the vtable; the concept checks it at compile time via the
 *     requires-clause. Both are LSP abstractions - sets of requirements.
 *   - A static_assert confirms the SAME type that derives from the base class
 *     also satisfies the concept; the expectations coincide by construction.
 *   - Use the runtime abstraction when you need heterogeneous collections or
 *     binary boundaries; use the compile-time abstraction when types are known
 *     and you want zero dispatch cost. The design intent is identical.
 *   - The book therefore uses one word, "concept", for both base classes and
 *     C++20 concepts (and pre-C++20 named template parameters) from here on.
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

// The RUNTIME abstraction (base class).
class DocumentBase
{
public:
    virtual ~DocumentBase() = default;
    virtual std::string exportToJSON() const = 0;
    virtual void serialize(ByteStream& bs) const = 0;
};

// The COMPILE-TIME abstraction (concept) - the SAME set of expected operations.
template <typename T>
concept DocumentConcept = requires(const T t, ByteStream& b)
{
    { t.exportToJSON() } -> std::convertible_to<std::string>;
    { t.serialize(b) };
};

// One concrete type that models BOTH abstractions at once. It derives from the
// base class (runtime) and, because it provides the operations, it also
// satisfies the concept (compile-time).
class PDF : public DocumentBase
{
public:
    std::string exportToJSON() const override { return R"({"format":"pdf"})"; }
    void serialize(ByteStream& bs) const override { bs.writeTag("PDF"); bs.writeBody("PDF-content"); }
};

// Runtime overload: depends on the base class, dispatched via the vtable.
void useDocumentRuntime(const DocumentBase& doc)
{
    ByteStream bs;
    doc.serialize(bs);
    std::cout << "  [runtime ]  json=" << doc.exportToJSON() << "  bytes=" << bs.str() << '\n';
}

// Compile-time overload: depends on the concept, resolved at compile time.
template <DocumentConcept T>
void useDocumentCompileTime(const T& doc)
{
    ByteStream bs;
    doc.serialize(bs);
    std::cout << "  [compile ]  json=" << doc.exportToJSON() << "  bytes=" << bs.str() << '\n';
}

int main()
{
    // The expectations coincide: a type that IS-A DocumentBase also satisfies
    // the DocumentConcept, because both encode the same required operations.
    static_assert(DocumentConcept<PDF>,
                  "PDF models the base-class interface, so it also models the concept");

    std::cout << "Same type, both abstractions - two sides of the same coin:\n";

    PDF pdf;
    useDocumentRuntime(pdf);     // bound at run time through the base class
    useDocumentCompileTime(pdf); // bound at compile time through the concept

    std::cout << "\nThe base class and the concept describe the same expectations;\n"
                 "useDocument() means the same thing in both styles and only the\n"
                 "moment of binding differs. That is why the book treats base\n"
                 "classes and concepts as the static and dynamic forms of one idea.\n";
    return 0;
}
