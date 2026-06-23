/*
 * Guideline 4 - Design for Testability (solution A: extract a free function)
 *
 * Instead of hiding the reorganization logic inside Widget's private section, we extract
 * it as a non-member non-friend free function in a detail namespace. The function takes
 * the blob vector by reference as its first argument - the data it used to reach through
 * the implicit this pointer. Widget keeps the vector private and simply calls the free
 * function, so encapsulation is preserved while the logic becomes a true, directly
 * testable interface.
 *
 * Key notes:
 *   - updateCollection() is now a free function: a test can call it with a plain
 *     std::vector of Blob - no Widget, no friend, no inheritance, no preprocessor hack.
 *   - This is a black-box test: it checks the observable behavior (empty blobs removed,
 *     sorted by size descending), not how Widget happens to call the function.
 *   - Scott Meyers' point: preferring non-member non-friend functions increases
 *     encapsulation, because the free function can touch only Widget's public interface,
 *     not its private data members.
 *   - Separation of concerns (SRP): if a piece of logic needs its own tests, that is a
 *     strong hint it changes for its own reasons and does not belong inside Widget.
 */
#pragma once

#include <algorithm>
#include <vector>

// The domain type, unchanged from the problem version.
struct Blob
{
    int id{ 0 };
    int size{ 0 };
};

namespace widgetDetails
{
    // The extracted "true interface": directly callable, directly testable. It receives
    // the collection explicitly rather than reaching for it via a this pointer.
    inline void updateCollection(std::vector<Blob>& blobs)
    {
        std::erase_if(blobs, [](const Blob& b) { return b.size <= 0; });
        std::sort(blobs.begin(), blobs.end(),
                  [](const Blob& a, const Blob& b) { return a.size > b.size; });
    }
} // namespace widgetDetails

// Widget keeps its data private and delegates to the free function. There is no friend
// declaration and no public getter added just for the sake of testing.
class Widget
{
public:
    void addBlob(const Blob& blob)
    {
        blobs_.push_back(blob);
        widgetDetails::updateCollection(blobs_); // pass blobs_ explicitly
    }

    std::size_t blobCount() const { return blobs_.size(); }

private:
    std::vector<Blob> blobs_;
};
