/*
 * Guideline 2 - Using the decoupled design (SOLUTION driver)
 *
 * This program wires the slimmed-down Document hierarchy (Document.h) together with the
 * separated JSON and Serialization components (Components.h). It demonstrates that a reader
 * of documents can use them through the small, cohesive Document interface, while JSON export
 * and serialization are requested explicitly from their own components only when needed. The
 * behavior is the same as the problem version, but the dependencies are not: a document, a
 * JSON change, and a serialization change are now three independent reasons to change living
 * in three independent places.
 *
 * Key notes:
 *   - printContent() depends on Document alone - no transitive coupling to JSON or ByteStream.
 *   - exportToJson() and serialize() are opt-in components, not obligations forced on every document.
 *   - To swap JSON library or change the byte format you would edit Components.cpp and nothing here.
 */

#include "Components.h"
#include "Document.h"

#include <iostream>
#include <memory>
#include <vector>

// A low-level consumer that only reads documents. It is coupled to Document and nothing else.
void printContent(const Document& doc)
{
    std::cout << "  content: " << doc.content() << '\n';
}

int main()
{
    std::vector<std::unique_ptr<Document>> docs;
    docs.push_back(std::make_unique<PdfDocument>("Hello PDF"));
    docs.push_back(std::make_unique<WordDocument>("Hello Word"));

    std::cout << "SOLUTION: concerns separated into independent variation points\n";
    for (const auto& doc : docs)
    {
        printContent(*doc);                                  // needs Document only
        std::cout << "  json:    " << exportToJson(*doc) << '\n'; // JSON component, opt-in
        std::cout << "  bytes:   " << serialize(*doc).size() << " byte(s)\n"; // serialization, opt-in
    }

    std::cout << "\nWhy this is easier to change:\n"
                 "  - Swapping the JSON library edits exportToJson() in one place only.\n"
                 "  - Changing the byte format edits serialize() in one place only.\n"
                 "  - Adding a document type does not force edits in unrelated documents.\n";
    return 0;
}
