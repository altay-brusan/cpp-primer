/*
 * Guideline 5 - Design for Extension (the closed design that violates the OCP)
 *
 * This is the naive serialization design from the book: a Document hierarchy
 * whose stored byte format is tagged with a central DocumentType enumeration,
 * and a serialize() function that switches over that enum. The design compiles
 * and runs, but it is closed for modification in the wrong way: adding a new
 * kind of document forces edits to existing, unrelated code. That couples every
 * document type to every other one through the shared enum plus switch, the
 * exact situation the Open-Closed Principle (OCP) warns against.
 *
 * Key notes:
 *   - The DocumentType enum artificially couples PDF and Word. PDF "knows about"
 *     the Word value and vice versa, even though they should be unaware of each
 *     other.
 *   - Adding an XML document means editing the enum AND the serialize() switch.
 *     At minimum that recompiles PDF and Word; at worst it blocks third parties
 *     who cannot edit the central enum from extending the code at all.
 *   - A forgotten switch case is silent: the compiler may not warn, so a new
 *     type can ship with a wrong or missing byte header. That is a real risk.
 *   - This file is the BEFORE picture. It is open for extension only by
 *     modifying code that already works, which is what the OCP advises against.
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

// The central type tag. Every document format must appear here, so all formats
// are coupled to this one enumeration on the same architectural level.
enum class DocumentType
{
    pdf,
    word,
    // A new format (xml) would have to be ADDED here, recompiling the rest.
};

class Document
{
public:
    virtual ~Document() = default;
    virtual DocumentType type() const = 0;
    virtual std::string content() const = 0;
};

class PDF : public Document
{
public:
    DocumentType type() const override { return DocumentType::pdf; }
    std::string content() const override { return "PDF-content"; }
};

class Word : public Document
{
public:
    DocumentType type() const override { return DocumentType::word; }
    std::string content() const override { return "Word-content"; }
};

// The closed extension point: this switch must be edited for every new format.
// It is the central place that violates the OCP.
ByteStream serialize(const Document& doc)
{
    ByteStream bs;
    switch (doc.type())
    {
        case DocumentType::pdf:  bs.writeTag("PDF");  break;
        case DocumentType::word: bs.writeTag("WORD"); break;
        // case DocumentType::xml: ... would have to be added HERE too.
    }
    bs.writeBody(doc.content());
    return bs;
}

int main()
{
    PDF pdf;
    Word word;

    std::cout << "Closed design (enum plus switch):\n";
    std::cout << "  " << serialize(pdf).str() << '\n';
    std::cout << "  " << serialize(word).str() << '\n';

    std::cout << "\nProblem: adding an XML document forces edits to the\n"
                 "DocumentType enum and the serialize() switch, recompiling\n"
                 "and re-coupling PDF and Word. That violates the OCP.\n";
    return 0;
}
