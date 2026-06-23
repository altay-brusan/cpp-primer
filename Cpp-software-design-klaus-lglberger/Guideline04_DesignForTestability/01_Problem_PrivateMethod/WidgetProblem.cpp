/*
 * Guideline 4 - Design for Testability (the problem: a private member is hard to test)
 *
 * Widget owns a collection of Blob objects that must be reorganized once in a while
 * through the updateCollection() member function. The book treats this function as
 * important enough that it deserves its own test, yet it lives in the private section,
 * so there is no direct way to call it from a test. This file shows the tempting but
 * flawed workarounds the book walks through: a white-box test through a public function,
 * and a friend test class. Both compile and run here, but each introduces an artificial
 * dependency that the next samples remove.
 *
 * Key notes:
 *   - A private member function cannot be called directly from the outside, so it cannot
 *     be tested directly. That is the core challenge of this guideline.
 *   - White-box test (through addBlob): the test depends on the internal detail that
 *     addBlob happens to call updateCollection. If addBlob is rewritten to stop calling
 *     it, the test silently stops testing updateCollection - you lose coverage unaware.
 *   - friend class TestWidget: technically works, but the production code now has to know
 *     about the test code, a cyclic and artificial dependency. In C plus plus, friend is
 *     not your friend - it introduces coupling.
 *   - Other rejected workarounds (described, not coded): making the function public (it
 *     guards an invariant and must not be called for fun), switching to protected plus
 *     inheriting a test class (abuses inheritance, nearly as open as public), and the
 *     hack of -Dprivate=public via the preprocessor (all is lost at that point).
 *   - The real cure, shown in samples 02 and 03, is separation of concerns: extract the
 *     function so it becomes a true, directly testable interface.
 */
#include <algorithm>
#include <iostream>
#include <vector>

// A tiny domain type. A Blob has an id and a size; a size of zero means it is empty.
struct Blob
{
    int id{ 0 };
    int size{ 0 };
};

class Widget
{
public:
    // Public behavior: adding a blob triggers a private reorganization of the collection.
    void addBlob(const Blob& blob)
    {
        blobs_.push_back(blob);
        updateCollection(); // internal detail that a white-box test would lean on
    }

    // The only public window a black-box test could use to observe the collection.
    std::size_t blobCount() const { return blobs_.size(); }
    int largestSize() const { return blobs_.empty() ? 0 : blobs_.front().size; }

    // The friend declaration below is workaround number 2: it lets a specific test class
    // reach into the private section. Note how production code now depends on test code.
    friend class TestWidget;

private:
    // The hard-to-test function: drop empty blobs, then keep the collection sorted by
    // size in descending order. It preserves an invariant, so it must stay non-public.
    void updateCollection()
    {
        std::erase_if(blobs_, [](const Blob& b) { return b.size <= 0; });
        std::sort(blobs_.begin(), blobs_.end(),
                  [](const Blob& a, const Blob& b) { return a.size > b.size; });
    }

    std::vector<Blob> blobs_;
};

// Workaround number 2 in code: a friend test fixture that calls the private function.
// It "works", but the existence of `friend class TestWidget;` inside Widget is exactly
// the artificial, cyclic coupling this guideline warns against.
class TestWidget
{
public:
    static bool privateCallSortsDescending()
    {
        Widget w;
        w.blobs_ = { Blob{ 1, 3 }, Blob{ 2, 9 }, Blob{ 3, 0 }, Blob{ 4, 5 } };
        w.updateCollection(); // reaching into the private section via friendship
        const bool emptyRemoved = (w.blobs_.size() == 3);
        const bool sorted = (w.blobs_[0].size == 9 && w.blobs_[1].size == 5 &&
                             w.blobs_[2].size == 3);
        return emptyRemoved && sorted;
    }
};

// A trivial hand-rolled check helper - no test framework, just a printed PASS or FAIL.
static int g_failures{ 0 };
static void check(bool cond, const char* name)
{
    std::cout << (cond ? "  PASS  " : "  FAIL  ") << name << '\n';
    if (!cond) { ++g_failures; }
}

int main()
{
    std::cout << "Guideline 4 - testing a PRIVATE member: the flawed workarounds\n\n";

    // Workaround 1: white-box test through the public addBlob function. We can only
    // observe the result indirectly, and we silently rely on addBlob calling the private
    // updateCollection. The day addBlob stops doing that, this "test" passes for the
    // wrong reason and our real coverage of updateCollection vanishes.
    {
        Widget w;
        w.addBlob(Blob{ 1, 3 });
        w.addBlob(Blob{ 2, 0 }); // empty: should be dropped by updateCollection
        w.addBlob(Blob{ 3, 9 });
        check(w.blobCount() == 2, "white-box: empty blob dropped via addBlob");
        check(w.largestSize() == 9, "white-box: largest blob sorted to front");
    }

    // Workaround 2: friend test class calling the private function directly.
    check(TestWidget::privateCallSortsDescending(),
          "friend class: direct private call (artificial coupling)");

    std::cout << "\nThese tests pass, but each depends on an internal detail or on a\n"
                 "friend declaration baked into production code. See 02 and 03 for the fix.\n";

    std::cout << (g_failures == 0 ? "\nAll checks passed.\n" : "\nSome checks FAILED.\n");
    return g_failures == 0 ? 0 : 1;
}
