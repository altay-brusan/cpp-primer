/*
 * Guideline 4 - Design for Testability (solution B: test the extracted class directly)
 *
 * This file tests widgetDetails::BlobCollection on its own, without ever constructing a
 * Widget. Because the once-private logic now lives in a class with a public interface, the
 * test simply creates a BlobCollection, drives it, and asserts the result. Widget is then
 * exercised through its public surface to confirm composition still works.
 *
 * Key notes:
 *   - Tests use <cassert> plus printed PASS or FAIL lines; no external test framework.
 *   - Testing the extracted class is black-box and needs no access to Widget internals.
 *   - The same separation-of-concerns reasoning as the free-function variant applies; this
 *     form is preferred when the extracted logic owns state.
 */
#include "BlobCollection.h"

#include <cassert>
#include <iostream>

static int g_failures{ 0 };
static void check(bool cond, const char* name)
{
    std::cout << (cond ? "  PASS  " : "  FAIL  ") << name << '\n';
    if (!cond) { ++g_failures; }
}

int main()
{
    std::cout << "Guideline 4 - testing an EXTRACTED CLASS directly\n\n";

    // Direct test of BlobCollection: no Widget required.
    {
        widgetDetails::BlobCollection coll;
        coll.addBlob(Blob{ 1, 3 });
        coll.addBlob(Blob{ 2, 9 });
        coll.addBlob(Blob{ 3, 0 }); // empty: must be dropped
        coll.addBlob(Blob{ 4, 5 });

        assert(coll.size() == 3);
        check(coll.size() == 3, "BlobCollection: empty blob removed");
        check(coll.at(0).size == 9 && coll.at(1).size == 5 && coll.at(2).size == 3,
              "BlobCollection: sorted by size descending");
    }

    // updateCollection can also be called explicitly and tested in isolation.
    {
        widgetDetails::BlobCollection coll;
        coll.addBlob(Blob{ 1, 2 });
        coll.updateCollection(); // idempotent on an already-tidy collection
        check(coll.size() == 1 && coll.at(0).size == 2,
              "BlobCollection: explicit updateCollection is stable");
    }

    // Production code still works: Widget composes a BlobCollection.
    {
        Widget w;
        w.addBlob(Blob{ 1, 0 }); // dropped
        w.addBlob(Blob{ 2, 7 });
        check(w.blobCount() == 1, "Widget: composes the extracted collection");
    }

    std::cout << (g_failures == 0 ? "\nAll checks passed.\n" : "\nSome checks FAILED.\n");
    return g_failures == 0 ? 0 : 1;
}
