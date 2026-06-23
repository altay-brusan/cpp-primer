/*
 * Guideline 24 - Object adapter (composition)
 *                (wrap the adaptee and forward to it)
 *
 * The fix from Guideline 24: introduce a Pages class that IS a Document and
 * HAS an OpenPages. Pages implements the expected interface (exportToJSON,
 * serialize) by forwarding each call to the matching OpenPages operation:
 * exportToJSON forwards to the free exportToJSONFormat, and serialize forwards
 * to the member convertToBytes. This is the Adapter design pattern, whose
 * intent is to convert the interface of a class into another interface clients
 * expect, so classes with incompatible interfaces can work together.
 *
 * Because Pages STORES an OpenPages instance, it is an OBJECT adapter. The book
 * prefers this form: it builds on composition (Guideline 20, Favor Composition
 * over Inheritance), which keeps it the more flexible default. The integration
 * is nonintrusive: neither OpenPages nor Document was modified. With Pages in
 * place, the same unchanged client from sample 01 now drives the Pages document
 * uniformly, side by side with Word.
 *
 * Key notes:
 *   - Object adapter == composition: the adapter owns an instance of the
 *     adaptee and delegates to it. Favor this form (see Guideline 20).
 *   - The mapping need not be one to one; an adapter freely maps the expected
 *     set of functions onto the available set (here a member and a free call).
 *   - Pages separates the interface concern from the implementation detail in
 *     OpenPages, supporting SRP and the open for extension idea (OCP).
 *   - Watch for LSP: only adapt when the adaptee truly honors the expectations
 *     of the target interface (the book's turkey is not a duck warning).
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

// The object adapter: IS a Document, HAS an OpenPages, forwards to it.
class Pages : public Document
{
public:
    explicit Pages(OpenPages pages) : pages_(std::move(pages)) {}

    void exportToJSON() const override
    {
        exportToJSONFormat(pages_);  // forward to the free function
    }
    void serialize(ByteStream& bs) const override
    {
        pages_.convertToBytes(bs);   // forward to the member function
    }

private:
    OpenPages pages_;  // the stored adaptee == object adapter
};

// The client is the SAME one from sample 01: it only knows Document.
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
    docs.push_back(std::make_unique<Pages>(OpenPages{"world"}));

    std::cout << "The same client now drives Word and Pages uniformly:\n";
    for (const auto& doc : docs)
        process(*doc);

    std::cout << "\nPages adapts OpenPages by composition and forwarding.\n"
                 "Neither OpenPages nor Document was modified: nonintrusive.\n";
    return 0;
}
