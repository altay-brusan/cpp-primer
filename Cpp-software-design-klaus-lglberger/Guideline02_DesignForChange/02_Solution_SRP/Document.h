/*
 * Guideline 2 - The slimmed-down Document hierarchy after separating concerns (SOLUTION part 1)
 *
 * This header is the refactored Document from the book: it keeps ONLY the fundamental
 * document operations and drops exportToJSON() and serialize() entirely. JSON export and
 * serialization are orthogonal aspects that change for different reasons, so they have been
 * moved out of the hierarchy into their own components (see Components.h). Because this header
 * no longer mentions any JSON type, any ByteStream, or any DocumentType enum, anyone who only
 * needs to read a document - the low-level User from the book - is no longer transitively
 * coupled to JSON or serialization. The header is now lightweight and reusable.
 *
 * Key notes:
 *   - The base class exposes a small, cohesive interface: things that genuinely belong to "a document".
 *   - Each variation point (JSON, serialization) is isolated elsewhere, so a change to one lands in
 *     exactly one place and cannot disturb the other or the documents themselves.
 *   - Concrete documents expose just enough data (content, a kind tag) for external components to
 *     do their work, without the documents knowing how that work is done.
 */

#pragma once

#include <string>

// A document only has to know what a document fundamentally is. Nothing about how it is
// exported or persisted leaks into this interface, so this header stays free of JSON,
// ByteStream, and DocumentType dependencies.
class Document
{
public:
    virtual ~Document() = default;

    // The cohesive, intrinsic operations of a document.
    virtual std::string content() const = 0;
    virtual std::string kind() const = 0; // a human-readable label, e.g. "pdf"
};

class PdfDocument : public Document
{
public:
    explicit PdfDocument(std::string body) : m_body{ std::move(body) } {}

    std::string content() const override { return m_body; }
    std::string kind() const override { return "pdf"; }

private:
    std::string m_body;
};

class WordDocument : public Document
{
public:
    explicit WordDocument(std::string body) : m_body{ std::move(body) } {}

    std::string content() const override { return m_body; }
    std::string kind() const override { return "word"; }

private:
    std::string m_body;
};
