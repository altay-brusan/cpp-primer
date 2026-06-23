/*
 * Guideline 3 - Fat interface couples unrelated concerns (the problem)
 *
 * This sample revisits the book's Document example. A single Document base class
 * is given two pure virtual functions that serve two completely orthogonal
 * concerns: exporting to JSON and binary serialization through a ByteStream.
 * Bundling both into one interface looks reasonable ("every document is both
 * exportable and serializable"), but it forces every client of Document to
 * depend on the whole interface, even on the parts it never calls. That is the
 * artificial coupling the Interface Segregation Principle warns about.
 *
 * Watch the exportDocument() function below: it only wants JSON, yet because it
 * takes a Document const reference it transitively depends on serialize() and on
 * the ByteStream type. Change ByteStream or serialize()'s signature and every
 * JSON-only client must be recompiled, retested, and possibly redeployed.
 *
 * Key notes:
 *   - This is BAD DESIGN on purpose; it compiles and runs to expose the smell.
 *   - The Interface Segregation Principle (ISP): clients should not be forced to
 *     depend on methods they do not use.
 *   - One fat interface aggregates orthogonal aspects, so any change to one
 *     aspect ripples to all users of the interface.
 *   - ByteStream is a tiny std-only stub standing in for a real serialization
 *     library, keeping the design point while staying self-contained.
 */
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

// Tiny stand-in for a real serialization buffer (no external library needed).
class ByteStream
{
public:
    void writeByte(std::uint8_t b) { m_bytes.push_back(b); }
    std::size_t size() const { return m_bytes.size(); }

private:
    std::vector<std::uint8_t> m_bytes;
};

// FAT INTERFACE: one base class forces two unrelated concerns onto every
// derived document, and therefore onto every client that touches a Document.
class Document
{
public:
    virtual ~Document() = default;

    // Concern A: human-readable JSON export.
    virtual std::string exportToJSON() const = 0;

    // Concern B: binary serialization through a ByteStream. Completely unrelated
    // to JSON, yet welded into the same interface.
    virtual void serialize(ByteStream& bs) const = 0;
};

class Invoice : public Document
{
public:
    explicit Invoice(int id, double total) : m_id{ id }, m_total{ total } {}

    std::string exportToJSON() const override
    {
        return "{ \"id\": " + std::to_string(m_id) +
               ", \"total\": " + std::to_string(m_total) + " }";
    }

    void serialize(ByteStream& bs) const override
    {
        // A throwaway "binary" encoding just to exercise the ByteStream stub.
        bs.writeByte(static_cast<std::uint8_t>(m_id & 0xFF));
        bs.writeByte(static_cast<std::uint8_t>(static_cast<int>(m_total) & 0xFF));
    }

private:
    int m_id{ 0 };
    double m_total{ 0.0 };
};

// This client ONLY wants JSON. But because it depends on the whole Document
// interface, it is artificially coupled to serialize() and to ByteStream too.
void exportDocument(Document const& doc)
{
    std::cout << "[exportDocument] " << doc.exportToJSON() << '\n';
}

int main()
{
    Invoice invoice{ 42, 199.0 };

    // The JSON-only use site still drags in the full Document interface.
    exportDocument(invoice);

    // Some other, unrelated part of the program performs serialization.
    ByteStream stream;
    invoice.serialize(stream);
    std::cout << "[serialize]      wrote " << stream.size() << " bytes\n";

    std::cout << "\nThe smell: exportDocument() needs only JSON, yet it depends\n"
                 "on serialize() and ByteStream through the fat Document interface.\n";
    return 0;
}
