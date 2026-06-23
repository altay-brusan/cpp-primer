/*
 * Guideline 2 - Implementation of the two isolated variation points (SOLUTION part 3)
 *
 * This translation unit is the single place that knows HOW JSON export and serialization
 * are done. If we ever switch from one JSON library to another, only exportToJson() changes.
 * If the binary format changes (endianness, type tag, framing), only serialize() changes.
 * The Document hierarchy and every reader of documents are completely unaffected, which is
 * exactly the "change in one place" outcome the Single-Responsibility Principle aims for.
 *
 * Key notes:
 *   - The JSON formatting decision is fully contained here; nothing leaks back into headers.
 *   - The DocumentType tag is local to serialization, so adding a new document kind does not
 *     ripple through unrelated documents the way the problem version's global enum did.
 */

#include "Components.h"

namespace
{
    // Serialization-local tag table. This is the ONLY code that needs to enumerate kinds,
    // so it does not couple the documents to one another.
    std::uint8_t typeTag(const std::string& kind)
    {
        if (kind == "pdf") { return 0; }
        if (kind == "word") { return 1; }
        return 255; // unknown
    }
}

std::string exportToJson(const Document& doc)
{
    // Swap this body to change JSON "library" - and nothing else in the codebase moves.
    return "{\"type\":\"" + doc.kind() + "\",\"content\":\"" + doc.content() + "\"}";
}

std::vector<std::uint8_t> serialize(const Document& doc)
{
    std::vector<std::uint8_t> bytes;
    bytes.push_back(typeTag(doc.kind()));
    for (char c : doc.content()) { bytes.push_back(static_cast<std::uint8_t>(c)); }
    return bytes;
}
