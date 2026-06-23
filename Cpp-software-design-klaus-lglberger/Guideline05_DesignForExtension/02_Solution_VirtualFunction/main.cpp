/*
 * Guideline 5 - Design for Extension (runtime extension via a base class)
 *
 * The same Document example, redesigned to obey the Open-Closed Principle. The
 * type tag plus central switch is gone; each document serializes itself through
 * a pure virtual serialize() member. The base class is the customization point:
 * a new format is added by deriving one new class and overriding one function,
 * with no edits to any existing document or to the code that drives them. The
 * design is open for extension but closed for modification.
 *
 * Key notes:
 *   - serialize() is virtual, so each type owns its own byte format. There is no
 *     shared enum, so PDF and Word are no longer aware of each other.
 *   - The XML class below is the NEW type. Note that adding it required touching
 *     nothing else: PDF and Word do not "see or feel a thing," not even a
 *     recompilation. That is what designing for extension buys you.
 *   - The driver loops over Document references and calls serialize()
 *     polymorphically. It is closed for modification yet works for every future
 *     type automatically.
 *   - Per the book, separating concerns (each type handling its own format)
 *     resolves the artificial coupling and the OCP violation at once.
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

// The base class IS the extension point. Each derived type plugs in its own
// serialization without any shared enum to couple the formats together.
class Document
{
public:
    virtual ~Document() = default;
    virtual void serialize(ByteStream& bs) const = 0;
};

class PDF : public Document
{
public:
    void serialize(ByteStream& bs) const override
    {
        bs.writeTag("PDF");
        bs.writeBody("PDF-content");
    }
};

class Word : public Document
{
public:
    void serialize(ByteStream& bs) const override
    {
        bs.writeTag("WORD");
        bs.writeBody("Word-content");
    }
};

// The NEW format. Adding XML touched no existing code: it is pure extension.
class XML : public Document
{
public:
    void serialize(ByteStream& bs) const override
    {
        bs.writeTag("XML");
        bs.writeBody("XML-content");
    }
};

int main()
{
    std::vector<std::unique_ptr<Document>> docs;
    docs.push_back(std::make_unique<PDF>());
    docs.push_back(std::make_unique<Word>());
    docs.push_back(std::make_unique<XML>()); // the freshly added type

    std::cout << "Open design (virtual serialize):\n";
    for (const auto& doc : docs)
    {
        ByteStream bs;
        doc->serialize(bs);
        std::cout << "  " << bs.str() << '\n';
    }

    std::cout << "\nXML was added by deriving one class and overriding one\n"
                 "function. No enum, no switch, no edits to PDF or Word: open\n"
                 "for extension, closed for modification.\n";
    return 0;
}
