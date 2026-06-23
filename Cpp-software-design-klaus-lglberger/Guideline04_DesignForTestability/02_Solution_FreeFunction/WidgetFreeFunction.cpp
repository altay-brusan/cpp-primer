/*
 * Guideline 4 - Design for Testability (solution A: test the extracted free function)
 *
 * This file tests the extracted widgetDetails::updateCollection() free function directly,
 * with nothing but a std::vector of Blob. No Widget instance, no friend class, no access
 * tricks - the function is part of a true interface, so the test is plain and honest.
 * The Widget itself is exercised separately through its public addBlob to show production
 * code still works after the extraction.
 *
 * Key notes:
 *   - Tests use <cassert> plus a printed PASS or FAIL line; no external test framework.
 *   - The free-function test is black-box: it asserts behavior (drop empties, sort by
 *     size descending), independent of how Widget uses the function.
 *   - Because the function no longer depends on Widget, it could be reused elsewhere and
 *     can change in isolation - coupling has been reduced.
 */
#include "Collection.h"

#include <cassert>
#include <iostream>
#include <vector>

static int g_failures{ 0 };
static void check(bool cond, const char* name)
{
    std::cout << (cond ? "  PASS  " : "  FAIL  ") << name << '\n';
    if (!cond) { ++g_failures; }
}

int main()
{
    std::cout << "Guideline 4 - testing an EXTRACTED FREE FUNCTION directly\n\n";

    // Direct, framework-free test of the extracted function. We need only a vector.
    {
        std::vector<Blob> blobs{ Blob{ 1, 3 }, Blob{ 2, 9 }, Blob{ 3, 0 }, Blob{ 4, 5 } };
        widgetDetails::updateCollection(blobs);

        // assert documents the invariant; the printed checks give a readable report.
        assert(blobs.size() == 3); // the size-zero blob was removed
        check(blobs.size() == 3, "free fn: empty blob removed");
        check(blobs[0].size == 9 && blobs[1].size == 5 && blobs[2].size == 3,
              "free fn: sorted by size descending");
    }

    // An already-sorted, empty-free collection must remain unchanged (stable behavior).
    {
        std::vector<Blob> blobs{ Blob{ 1, 8 }, Blob{ 2, 4 }, Blob{ 3, 1 } };
        widgetDetails::updateCollection(blobs);
        check(blobs.size() == 3 && blobs[0].size == 8 && blobs[2].size == 1,
              "free fn: already-tidy collection is left in order");
    }

    // Production code still works: Widget delegates to the same free function.
    {
        Widget w;
        w.addBlob(Blob{ 1, 3 });
        w.addBlob(Blob{ 2, 0 });
        w.addBlob(Blob{ 3, 9 });
        check(w.blobCount() == 2, "Widget: still drops empties via the free function");
    }

    std::cout << (g_failures == 0 ? "\nAll checks passed.\n" : "\nSome checks FAILED.\n");
    return g_failures == 0 ? 0 : 1;
}
