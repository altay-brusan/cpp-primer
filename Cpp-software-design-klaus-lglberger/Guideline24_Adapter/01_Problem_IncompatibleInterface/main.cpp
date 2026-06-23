/*
 * Guideline 24 - The problem: an incompatible interface
 *                (a useful class that does not fit the expected interface)
 *
 * The book's Document example. A client works against a small, segregated
 * interface: a Document is JSONExportable (it offers exportToJSON) and
 * Serializable (it offers serialize). The existing Word document implements
 * both, so any code written against Document just works.
 *
 * Then a third-party class, OpenPages, shows up. It can do everything we need,
 * but speaks a DIFFERENT dialect: serialization is a member named
 * convertToBytes, and JSON export is a FREE function exportToJSONFormat. It also
 * does not derive from Document. So even though the functionality is right
 * there, OpenPages cannot be dropped into code that expects a Document. The
 * interfaces are incompatible.
 *
 * This file compiles and runs: Word flows through the client cleanly, while
 * OpenPages can only be driven by its own native calls. The marked line shows
 * the call the client would like to make but cannot. Guideline 24's Adapter
 * pattern (samples 02 and 03) closes that gap without touching either side.
 *
 * Key notes:
 *   - The client depends on the abstraction Document, not on concrete types.
 *   - OpenPages is the adaptee: correct behavior, wrong interface and wrong
 *     base, and we are not allowed to modify it (it is third-party code here).
 *   - Without an adapter the two worlds stay disconnected: no shared base, no
 *     uniform call site.
 */
#include <iostream>
#include <string>
#include <string_view>
#include <utility>

// A tiny stand-in for a serialization buffer (the book's ByteStream).
class ByteStream
{
public:
    void append(std::string_view chunk) { data_ += chunk; }
    const std::string& str() const { return data_; }

private:
    std::string data_;
};

// Segregated interfaces, exactly as the client expects them.
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

// The abstraction the client codes against.
class Document : public JSONExportable, public Serializable
{
};

// An existing document type that already fits the interface.
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

// The third-party adaptee: useful, but with an incompatible interface.
// Note the names: convertToBytes (not serialize) and a FREE exportToJSONFormat
// (not a member exportToJSON). It also does NOT derive from Document.
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

// The client: it only knows how to drive a Document.
void process(const Document& doc)
{
    ByteStream bs;
    doc.serialize(bs);
    doc.exportToJSON();
    std::cout << "  bytes: " << bs.str() << "\n";
}

int main()
{
    std::cout << "Client driving a Word through the Document interface:\n";
    Word word{"hello"};
    process(word);

    std::cout << "\nOpenPages can only be driven by its own native calls:\n";
    OpenPages pages{"world"};
    ByteStream bs;
    pages.convertToBytes(bs);   // not serialize
    exportToJSONFormat(pages);  // free function, not a member
    std::cout << "  bytes: " << bs.str() << "\n";

    // process(pages);          // will NOT compile: OpenPages is not a Document
    std::cout << "\nThe useful OpenPages cannot reach process(): its interface is\n"
                 "incompatible and it is not a Document. An Adapter fixes this.\n";
    return 0;
}
