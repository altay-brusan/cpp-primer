/*
 * Guideline 3 - Segregate interfaces to separate concerns (the solution)
 *
 * Here we apply the Interface Segregation Principle to the Document example. The
 * single fat interface is split into two focused interfaces representing the two
 * orthogonal aspects: JSONExportable and Serializable. The concrete Document
 * still represents the full requirement on all documents by inheriting from
 * both, so nothing is lost. What changes is what CLIENTS depend on.
 *
 * The exportDocument() function now takes a JSONExportable const reference, so it
 * depends only on exportToJSON() and no longer on serialize() or on ByteStream.
 * Changing serialization can no longer ripple into JSON-only clients. The
 * segregation of interfaces has decoupled two concerns that never belonged
 * together, exactly as the book recommends.
 *
 * Key notes:
 *   - ISP is a special case of the Single-Responsibility Principle aimed at
 *     interfaces: one interface, one reason to change.
 *   - Clients depend only on the segregated interface they actually use, so the
 *     blast radius of any change shrinks to the matching concern.
 *   - Document still aggregates both roles via multiple inheritance; the SRP is
 *     applied to the interface, not removed from the type.
 *   - ByteStream remains a tiny std-only stub so the sample is self-contained.
 */
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

class ByteStream
{
public:
    void writeByte(std::uint8_t b) { m_bytes.push_back(b); }
    std::size_t size() const { return m_bytes.size(); }

private:
    std::vector<std::uint8_t> m_bytes;
};

// SEGREGATED INTERFACE A: only the JSON concern.
class JSONExportable
{
public:
    virtual ~JSONExportable() = default;
    virtual std::string exportToJSON() const = 0;
};

// SEGREGATED INTERFACE B: only the serialization concern. Note that ByteStream
// is mentioned here and nowhere near the JSON interface.
class Serializable
{
public:
    virtual ~Serializable() = default;
    virtual void serialize(ByteStream& bs) const = 0;
};

// Document still expresses the full requirement on every document, but now as a
// composition of two independent roles.
class Document : public JSONExportable, public Serializable
{
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
        bs.writeByte(static_cast<std::uint8_t>(m_id & 0xFF));
        bs.writeByte(static_cast<std::uint8_t>(static_cast<int>(m_total) & 0xFF));
    }

private:
    int m_id{ 0 };
    double m_total{ 0.0 };
};

// Depends ONLY on the JSON concern. It cannot even name ByteStream now, so a
// change to serialization can never force a recompile here.
void exportDocument(JSONExportable const& exportable)
{
    std::cout << "[exportDocument] " << exportable.exportToJSON() << '\n';
}

// A separate client depends only on the serialization concern.
void backupDocument(Serializable const& serializable)
{
    ByteStream stream;
    serializable.serialize(stream);
    std::cout << "[backupDocument] wrote " << stream.size() << " bytes\n";
}

int main()
{
    Invoice invoice{ 42, 199.0 };

    // Each client sees exactly one concern through its segregated interface.
    exportDocument(invoice);
    backupDocument(invoice);

    std::cout << "\nThe fix: exportDocument() depends only on JSONExportable,\n"
                 "so the serialization concern and ByteStream are fully decoupled\n"
                 "from JSON-only clients.\n";
    return 0;
}
