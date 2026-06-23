/*
 * Guideline 7 - Understand the Similarities Between Base Classes and Concepts
 *               (the RUNTIME abstraction: a base class with virtual functions)
 *
 * This sample shows the dynamic (runtime) polymorphism side of the duality the
 * book describes. A Document base class declares a set of pure virtual
 * operations - exportToJSON() and serialize() - and useDocument() is written
 * against that base class only. The function therefore works with ANY class
 * derived from Document, that is, with any class that adheres to the
 * expectations of the Document abstraction. Which concrete override actually
 * runs is resolved at run time through the vtable (dynamic dispatch).
 *
 * The point of the guideline is that this base class is, semantically, a formal
 * description of expected behavior: a set of syntactic AND semantic
 * requirements that calling code relies on. In sample 02 we express the SAME
 * requirement as a C++20 concept and see that, apart from when the binding
 * happens, the two are two sides of the same coin.
 *
 * Key notes:
 *   - A base class with virtual functions is a RUNTIME abstraction. The set of
 *     expected operations is the set of (pure) virtual functions.
 *   - useDocument(Document const&) is decoupled from concrete types; it depends
 *     only on the abstraction. New document types can be added without touching
 *     it - they just have to satisfy the abstraction.
 *   - Dispatch is dynamic: a heterogeneous container of Document pointers can
 *     hold mixed concrete types and the right override runs for each at run time.
 *   - The Liskov Substitution Principle (LSP) applies: every derived type must
 *     honor the expected behavior, not merely the function signatures.
 */
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

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

// The RUNTIME abstraction: a base class whose pure virtual functions ARE the
// set of expected operations. Any derived type must provide them.
class Document
{
public:
    virtual ~Document() = default;
    virtual std::string exportToJSON() const = 0;
    virtual void serialize(ByteStream& bs) const = 0;
};

class PDF : public Document
{
public:
    std::string exportToJSON() const override { return R"({"format":"pdf"})"; }
    void serialize(ByteStream& bs) const override { bs.writeTag("PDF"); bs.writeBody("PDF-content"); }
};

class Word : public Document
{
public:
    std::string exportToJSON() const override { return R"({"format":"word"})"; }
    void serialize(ByteStream& bs) const override { bs.writeTag("WORD"); bs.writeBody("Word-content"); }
};

// Written against the abstraction only. Works with any class derived from
// Document, i.e. any class adhering to the expectations of the abstraction.
// The concrete override is selected at run time (dynamic dispatch).
void useDocument(const Document& doc)
{
    ByteStream bs;
    doc.serialize(bs);
    std::cout << "  json=" << doc.exportToJSON() << "  bytes=" << bs.str() << '\n';
}

int main()
{
    std::cout << "Runtime abstraction (base class + virtual functions):\n";

    PDF pdf;
    Word word;
    useDocument(pdf);
    useDocument(word);

    // A heterogeneous container: only possible with runtime polymorphism.
    std::cout << "\nHeterogeneous collection dispatched at run time:\n";
    std::vector<std::unique_ptr<Document>> docs;
    docs.push_back(std::make_unique<PDF>());
    docs.push_back(std::make_unique<Word>());
    for (const auto& d : docs)
    {
        useDocument(*d);
    }

    std::cout << "\nThe base class is the abstraction: a formal set of expected\n"
                 "operations. useDocument() depends only on it, and the right\n"
                 "override is bound dynamically. Sample 02 states the SAME\n"
                 "expectations as a C++20 concept, bound at compile time.\n";
    return 0;
}
