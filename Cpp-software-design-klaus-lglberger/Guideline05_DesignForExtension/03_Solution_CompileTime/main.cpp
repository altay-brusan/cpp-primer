/*
 * Guideline 5 - Design for Extension (compile-time extension via an overload set)
 *
 * The book stresses that the OCP is not only about runtime polymorphism: the
 * Standard Library is designed for extension with no base classes at all, using
 * function overloading (std::swap), templates (std::find), and template
 * specialization (std::hash). This sample mirrors the std::swap customization
 * point: a generic algorithm calls an unqualified serialize(), and any value
 * type plugs in by providing its own free serialize() overload found through
 * argument dependent lookup (ADL). No base class, no shared enum.
 *
 * Key notes:
 *   - toBytes() is the closed-for-modification algorithm. It never changes, yet
 *     it works for any type that supplies a serialize() overload.
 *   - Each type lives in its own namespace and brings its own serialize() as a
 *     free function. Adding a type adds code only; nothing existing is edited.
 *   - The unqualified call "serialize(obj, bs)" plus the using-declaration lets
 *     ADL select the right overload, exactly as the book shows for std::swap.
 *   - There is no inheritance here. Compile-time extension points (overload
 *     sets, templates, specialization) satisfy the OCP just as base classes do.
 */
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

// A default serialize() the algorithm can fall back to (like a generic
// std::swap). Custom types override it by providing a better-matching overload.
namespace serial
{
    template <typename T>
    void serialize(const T&, ByteStream& bs)
    {
        bs.writeTag("UNKNOWN");
        bs.writeBody("?");
    }
}

// Two value types, each in its own namespace with its own free serialize().
namespace fmt
{
    struct PDF { std::string body{ "PDF-content" }; };

    void serialize(const PDF& doc, ByteStream& bs)
    {
        bs.writeTag("PDF");
        bs.writeBody(doc.body);
    }

    // The NEW type. Its serialize() overload is the only thing that was added.
    struct XML { std::string body{ "XML-content" }; };

    void serialize(const XML& doc, ByteStream& bs)
    {
        bs.writeTag("XML");
        bs.writeBody(doc.body);
    }
}

// The generic algorithm: closed for modification, open for any type via ADL.
template <typename T>
ByteStream toBytes(const T& obj)
{
    using serial::serialize; // enable the generic fallback to be considered
    ByteStream bs;
    serialize(obj, bs);      // unqualified: ADL picks the type's own overload
    return bs;
}

int main()
{
    fmt::PDF pdf;
    fmt::XML xml;

    std::cout << "Compile-time design (overload set plus ADL):\n";
    std::cout << "  " << toBytes(pdf).str() << '\n';
    std::cout << "  " << toBytes(xml).str() << '\n';

    std::cout << "\nXML plugged into the same toBytes() algorithm by adding one\n"
                 "free serialize() overload. No base class, no edits to PDF or to\n"
                 "toBytes(): the Standard-Library style of designing for extension.\n";
    return 0;
}
