/*
 * Guideline 4 - Design for Testability (solution B: extract a class for stateful logic)
 *
 * When the reorganization logic has state of its own, the book suggests extracting it as
 * a separate class rather than a single free function. Here widgetDetails::BlobCollection
 * owns the vector of Blob and exposes a public updateCollection() plus small observers.
 * Widget holds a BlobCollection instead of a raw vector, so the collection logic becomes
 * an independent, directly testable unit, and Widget itself becomes more encapsulated.
 *
 * Key notes:
 *   - BlobCollection has a public, directly testable interface - no friend or inheritance
 *     tricks are needed to test the previously-private behavior.
 *   - BlobCollection cannot touch Widget's non-public members, so Widget gains a little
 *     extra encapsulation, exactly as Meyers argues for extracted functionality.
 *   - This is the right choice when the logic carries state; the free-function form in
 *     sample 02 is the right choice when it does not.
 *   - The class lives in a detail namespace to signal it is an implementation collaborator
 *     of Widget, not part of Widget's public surface.
 */
#pragma once

#include <algorithm>
#include <vector>

struct Blob
{
    int id{ 0 };
    int size{ 0 };
};

namespace widgetDetails
{
    // The extracted, self-contained collection. It owns the blobs and the logic that used
    // to be Widget's private member function, and it is trivially testable on its own.
    class BlobCollection
    {
    public:
        void addBlob(const Blob& blob)
        {
            blobs_.push_back(blob);
            updateCollection();
        }

        // The behavior that was hard to test as a Widget private member is now public here.
        void updateCollection()
        {
            std::erase_if(blobs_, [](const Blob& b) { return b.size <= 0; });
            std::sort(blobs_.begin(), blobs_.end(),
                      [](const Blob& a, const Blob& b) { return a.size > b.size; });
        }

        std::size_t size() const { return blobs_.size(); }
        const Blob& at(std::size_t i) const { return blobs_.at(i); }

    private:
        std::vector<Blob> blobs_;
    };
} // namespace widgetDetails

// Widget now composes a BlobCollection. It exposes only what users need and delegates the
// collection handling to the extracted, separately tested class.
class Widget
{
public:
    void addBlob(const Blob& blob) { blobs_.addBlob(blob); }
    std::size_t blobCount() const { return blobs_.size(); }

private:
    widgetDetails::BlobCollection blobs_;
};
