/*
 * Guideline 3 - ISP also applies to templates (minimize requirements)
 *
 * The book stresses that the Interface Segregation Principle is not limited to
 * base classes. A template's constraints ARE its interface, so over-constraining
 * a template couples it to operations it does not need. The book's example is
 * std::copy, which deliberately requires only an input iterator for the source
 * and an output iterator for the destination, never the stronger forward
 * iterator. That minimal requirement is what lets std::copy read from things
 * like input streams that offer no multipass guarantee.
 *
 * Below, myCopy is constrained with exactly the two capabilities it uses, so it
 * happily copies from a single-pass istream-style source. A static_assert then
 * documents that an over-constrained version demanding forward_iterator would
 * reject that same single-pass source, illustrating the artificial coupling ISP
 * removes from generic code.
 *
 * Key notes:
 *   - For templates the "interface" is the set of concept constraints; requiring
 *     more than you use is the same coupling smell as a fat base class.
 *   - std::input_iterator plus std::output_iterator is the minimal requirement
 *     for a copy; demanding std::forward_iterator would over-constrain it.
 *   - A single-pass source models input_iterator but not forward_iterator, so an
 *     over-constrained algorithm would needlessly exclude it.
 *   - Everything here is standard-library only.
 */
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

// myCopy requires ONLY what it uses: read from an input range, write to an
// output iterator. This mirrors std::copy's segregated requirements.
template <std::input_iterator InputIt, std::output_iterator<std::iter_value_t<InputIt>> OutputIt>
OutputIt myCopy(InputIt first, InputIt last, OutputIt dFirst)
{
    for (; first != last; ++first, ++dFirst)
    {
        *dFirst = *first;
    }
    return dFirst;
}

int main()
{
    // A single-pass source: istream_iterator is an input iterator, NOT a forward
    // iterator (no multipass guarantee), just like reading from std::cin.
    std::istringstream input{ "10 20 30 40" };
    std::istream_iterator<int> begin{ input };
    std::istream_iterator<int> end{};

    std::vector<int> destination;
    myCopy(begin, end, std::back_inserter(destination));

    std::cout << "Copied from a single-pass input source: ";
    for (int value : destination)
    {
        std::cout << value << ' ';
    }
    std::cout << '\n';

    // Document the ISP point at compile time: the single-pass source satisfies
    // the minimal input_iterator requirement but NOT the stronger forward
    // requirement. An over-constrained "forward_iterator" copy would reject it.
    static_assert(std::input_iterator<std::istream_iterator<int>>,
                  "istream_iterator must model input_iterator");
    static_assert(!std::forward_iterator<std::istream_iterator<int>>,
                  "istream_iterator must NOT model forward_iterator (single pass)");

    std::cout << "\nMinimal constraints (input plus output) keep myCopy usable\n"
                 "with single-pass sources; an over-constrained forward_iterator\n"
                 "requirement would couple it to capabilities it never needs.\n";
    return 0;
}
