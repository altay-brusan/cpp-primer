/*
 * Guideline 24 - Class adapter (private inheritance)
 *                (inherit the adaptee instead of storing it)
 *
 * The same Pages adapter, written the other way the book describes: a CLASS
 * adapter. Instead of storing an OpenPages member, Pages inherits from it,
 * nonpublicly. Private inheritance means is-implemented-in-terms-of, not is-a:
 * the OpenPages interface stays hidden from the outside, while Pages still
 * exposes only the Document interface. serialize forwards to the inherited
 * convertToBytes, and exportToJSON passes the object itself to the free
 * exportToJSONFormat by converting the private base (this is allowed inside a
 * member of the derived class).
 *
 * The book is clear about the trade-off: object adapters (sample 02) are more
 * flexible and should be your default, per Guideline 20, Favor Composition over
 * Inheritance. A class adapter earns its keep only in a few cases, for example
 * when you must override a virtual of the adaptee, need a protected member,
 * require a specific base construction order, share a virtual base, or want the
 * Empty Base Optimization. Otherwise prefer the object adapter.
 *
 * Key notes:
 *   - Class adapter == (private) inheritance of the adaptee; object adapter ==
 *     composition. Same intent, different mechanism.
 *   - Private inheritance hides the adaptee interface, so Pages is usable only
 *     as a Document, never as an OpenPages, from the outside.
 *   - Inside a Pages member, the upcast to the private OpenPages base is legal,
 *     which is why exportToJSONFormat(*this) compiles here but not externally.
 *   - Reach for this form only for the specific reasons above; default to the
 *     object adapter.
 */
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

class ByteStream
{
public:
    void append(std::string_view chunk) { data_ += chunk; }
    const std::string& str() const { return data_; }

private:
    std::string data_;
};

class JSONExportable
{
public:
    virtual ~JSONExportable() = default;
    virtual void exportToJSON() const = 0;
};

class Serializable
{
public:
    virtual ~Serializable() = default;
    virtual void serialize(ByteStream& bs) const = 0;
};

class Document : public JSONExportable, public Serializable
{
};

class Word : public Document
{
public:
    explicit Word(std::string text) : text_(std::move(text)) {}

    void exportToJSON() const override
    {
        std::cout << "{ \"word\": \"" << text_ << "\" }\n";
    }
    void serialize(ByteStream& bs) const override
    {
        bs.append("WORD:");
        bs.append(text_);
    }

private:
    std::string text_;
};

// The third-party adaptee (unchanged from sample 01).
class OpenPages
{
public:
    explicit OpenPages(std::string text) : text_(std::move(text)) {}

    void convertToBytes(ByteStream& bs) const
    {
        bs.append("PAGES:");
        bs.append(text_);
    }
    const std::string& content() const { return text_; }

private:
    std::string text_;
};

void exportToJSONFormat(const OpenPages& pages)
{
    std::cout << "{ \"pages\": \"" << pages.content() << "\" }\n";
}

// The class adapter: IS a Document, and IS-IMPLEMENTED-IN-TERMS-OF OpenPages
// via private inheritance.
class Pages : public Document, private OpenPages
{
public:
    explicit Pages(std::string text) : OpenPages(std::move(text)) {}

    void exportToJSON() const override
    {
        exportToJSONFormat(*this);  // upcast to the private base, legal here
    }
    void serialize(ByteStream& bs) const override
    {
        this->convertToBytes(bs);   // inherited member
    }
};

// The client is unchanged: it only knows Document.
void process(const Document& doc)
{
    ByteStream bs;
    doc.serialize(bs);
    doc.exportToJSON();
    std::cout << "  bytes: " << bs.str() << "\n";
}

int main()
{
    std::vector<std::unique_ptr<Document>> docs;
    docs.push_back(std::make_unique<Word>("hello"));
    docs.push_back(std::make_unique<Pages>("world"));

    std::cout << "Class adapter: Pages privately inherits OpenPages.\n";
    for (const auto& doc : docs)
        process(*doc);

    std::cout << "\nSame result as the object adapter, but built on inheritance.\n"
                 "Prefer the object adapter unless a special reason applies.\n";
    return 0;
}
