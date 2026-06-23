/*
 * Guideline 2 - The Document base class that couples orthogonal concerns (the PROBLEM)
 *
 * This file shows the "great-looking but bad" abstract Document class from the book:
 * a base class that bundles the document data together with two completely unrelated
 * aspects, JSON export and binary serialization. It compiles and runs perfectly, yet
 * it is poor software design because it manufactures artificial dependencies. Every
 * class deriving from Document is forced to depend on a particular JSON formatting
 * decision, on the ByteStream serialization format, and on the global DocumentType
 * enumeration that lists every document kind. These three orthogonal aspects change
 * for different reasons, so combining them into one interface means the whole hierarchy
 * changes for many reasons - a direct violation of the Single-Responsibility Principle.
 *
 * Key notes:
 *   - The book uses a real third-party JSON library here. The standard-library-only rule
 *     forbids that, so a tiny inline "JsonValue" stub stands in for it. The DESIGN flaw is
 *     identical: deriving classes are coupled to a JSON formatting decision they did not ask for.
 *   - exportToJSON() being pure virtual forces every document to re-implement JSON, so a switch
 *     to a different JSON library would ripple through every derived class (a change in many places).
 *   - serialize() couples documents to the ByteStream format AND to the DocumentType enum, so
 *     adding a new document type (say "spreadsheet") edits an enum that every other document reads,
 *     making every existing document implicitly know about every other one.
 *   - A low-level User only wants to read a document, yet it transitively drags in JSON and
 *     serialization - an artificial, not intrinsic, dependency. That is the whole problem.
 *   - This is intentionally bad DESIGN, not bad syntax: it builds and runs so you can see the smell.
 */

#include <iostream>
#include <memory>
#include <string>
#include <vector>

// --------------------------------------------------------------------------------------
// Stub for a third-party JSON library. In the book this would be json / rapidjson /
// simdjson included via <some_json_library.h> - a physical dependency the Document header
// would then leak to everyone who includes it. We keep the coupling, drop the real include.
// --------------------------------------------------------------------------------------
struct JsonValue
{
    std::string text; // pretend this is a rich JSON document object model node
};

// Stub for the serialization sink. The book's ByteStream is a direct, necessary-looking
// dependency that the Document base class drags into the whole hierarchy.
struct ByteStream
{
    std::vector<unsigned char> bytes;
    void put(unsigned char b) { bytes.push_back(b); }
};

// Global enumeration that lists EVERY kind of document. Because serialize() writes this
// tag into the byte stream, every derived class must know this enum exists, and adding a
// new document type forces an edit here that is observed by all existing documents.
enum class DocumentType : unsigned char
{
    pdf,
    word
    // ... potentially many more document types, each one a global ripple.
};

// --------------------------------------------------------------------------------------
// The over-loaded base class: data plus JSON plus serialization, all in one interface.
// --------------------------------------------------------------------------------------
class Document
{
public:
    virtual ~Document() = default;

    // Intrinsic, fine: the genuine document operation.
    virtual std::string content() const = 0;

    // ARTIFICIAL aspect #1: forces a JSON formatting decision on every derived class,
    // and (worse) the JsonValue return type leaks an implementation detail of the chosen
    // library into the signature, so swapping libraries changes every caller too.
    virtual JsonValue exportToJSON() const = 0;

    // ARTIFICIAL aspect #2: couples every derived class to the ByteStream format and to
    // the DocumentType enum. JSON export and serialization are orthogonal, yet here a
    // change to one sits right next to the other in the same class.
    virtual void serialize(ByteStream& stream) const = 0;
};

// --------------------------------------------------------------------------------------
// Two concrete documents. Notice how each one must re-implement BOTH unrelated aspects,
// duplicating the JSON-quoting logic and duplicating the serialization framing logic.
// --------------------------------------------------------------------------------------
class PdfDocument : public Document
{
public:
    explicit PdfDocument(std::string body) : m_body{ std::move(body) } {}

    std::string content() const override { return m_body; }

    JsonValue exportToJSON() const override
    {
        // Coupled to a JSON formatting decision the document author had to make.
        return JsonValue{ "{\"type\":\"pdf\",\"content\":\"" + m_body + "\"}" };
    }

    void serialize(ByteStream& stream) const override
    {
        // Coupled to BOTH the serialization framing AND the global DocumentType enum.
        stream.put(static_cast<unsigned char>(DocumentType::pdf));
        for (char c : m_body) { stream.put(static_cast<unsigned char>(c)); }
    }

private:
    std::string m_body;
};

class WordDocument : public Document
{
public:
    explicit WordDocument(std::string body) : m_body{ std::move(body) } {}

    std::string content() const override { return m_body; }

    JsonValue exportToJSON() const override
    {
        // Same JSON decision duplicated here - if the format changes it changes in two places.
        return JsonValue{ "{\"type\":\"word\",\"content\":\"" + m_body + "\"}" };
    }

    void serialize(ByteStream& stream) const override
    {
        stream.put(static_cast<unsigned char>(DocumentType::word));
        for (char c : m_body) { stream.put(static_cast<unsigned char>(c)); }
    }

private:
    std::string m_body;
};

// --------------------------------------------------------------------------------------
// A low-level consumer that only wants to READ a document. It never asks for JSON or
// serialization, yet because those aspects live in the Document interface, User is now
// transitively coupled to the JSON stub, ByteStream, and DocumentType. That is the
// artificial, transitive coupling the book warns about.
// --------------------------------------------------------------------------------------
void printContent(const Document& doc)
{
    std::cout << "  content: " << doc.content() << '\n';
}

int main()
{
    std::vector<std::unique_ptr<Document>> docs;
    docs.push_back(std::make_unique<PdfDocument>("Hello PDF"));
    docs.push_back(std::make_unique<WordDocument>("Hello Word"));

    std::cout << "PROBLEM: one class mixing three orthogonal concerns\n";
    for (const auto& doc : docs)
    {
        printContent(*doc);                       // intrinsic use - all anyone wanted
        std::cout << "  json:    " << doc->exportToJSON().text << '\n'; // coupled aspect 1
        ByteStream stream;
        doc->serialize(stream);                    // coupled aspect 2
        std::cout << "  bytes:   " << stream.bytes.size() << " byte(s)\n";
    }

    std::cout << "\nWhy this hurts changeability:\n"
                 "  - Switching JSON library changes every derived class (and signatures).\n"
                 "  - Serialization format and JSON export change for different reasons but live together.\n"
                 "  - Adding a document type edits DocumentType, which every document already depends on.\n";
    return 0;
}
