/*
 * Guideline 29 - Be Aware of Bridge Performance Gains and Losses
 *                (Bridge/Pimpl costs an indirection, but a PARTIAL Bridge can
 *                 IMPROVE performance by keeping hot data inline)
 *
 * The book takes the Bridge from Guideline 28 and asks the honest question:
 * what does the pointer indirection cost? It benchmarks three layouts of a
 * Person type, all holding the same logical data (six strings plus a year of
 * birth), and repeatedly finds the oldest person with std::min_element over a
 * large vector. The only thing that varies is WHERE the data lives:
 *
 *   (a) PersonInline      - all members inline, no Bridge (the baseline).
 *   (b) PersonFullPimpl   - every member moved behind a unique_ptr (full Pimpl).
 *   (c) PersonPartial     - HOT data (forename, surname, year) inline; COLD data
 *                           (address, city, country, zip) behind the pointer.
 *
 * The book's finding: full Pimpl is ~11-13 percent SLOWER than inline, because
 * the year now sits in a scattered heap block and every access is an indirection
 * with poor cache locality. The partial Bridge is ~6-14 percent FASTER than
 * inline, because moving the rarely-touched cold data out shrinks the object
 * (here ~200 bytes down to ~80), so the hot loop streams through far fewer cache
 * lines. The operation looks compute-bound but is in fact memory-bound: with a
 * 64-byte cache line the inline layout uses only a few percent of every line it
 * loads. Smaller stride means fewer wasted bytes.
 *
 * This is one .cpp so all three Impl structs are visible here; in real code the
 * Impl would live in a .cpp and the destructor would be defined out-of-line.
 *
 * Key notes:
 *   - A Bridge generally COSTS performance (extra hop, heap block, worse
 *     locality, lost inlining). Do not reach for it expecting it to be free.
 *   - A PARTIAL Bridge can GAIN performance: separate frequently-used from
 *     rarely-used data, keep the hot members inline, push the cold ones behind
 *     the pointer. The smaller object improves cache behavior on hot loops.
 *   - There is a whole range between the two extremes; you decide per case where
 *     hiding implementation details should yield to inlining hot members.
 *   - MEASURE, do not guess. The numbers depend on element count, member sizes,
 *     the machine, and the computation. Confirm with a representative benchmark.
 */
#include <algorithm>
#include <chrono>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <vector>

// ----- (a) No Bridge: every data member lives inline in the object. ---------
// Largest footprint, so the hot loop drags a lot of unused bytes through cache.
class PersonInline
{
public:
    PersonInline(std::string forename, std::string surname, std::string address,
                 std::string city, std::string country, std::string zip, int year)
        : m_forename{std::move(forename)}
        , m_surname{std::move(surname)}
        , m_address{std::move(address)}
        , m_city{std::move(city)}
        , m_country{std::move(country)}
        , m_zip{std::move(zip)}
        , m_year{year}
    {
    }

    int yearOfBirth() const { return m_year; } // direct read, no indirection

private:
    std::string m_forename;
    std::string m_surname;
    std::string m_address;
    std::string m_city;
    std::string m_country;
    std::string m_zip;
    int m_year;
};

// ----- (b) Full Pimpl: ALL data lives behind a unique_ptr. ------------------
// The object is tiny (one pointer), but reading the year hops to a scattered
// heap block every time: the indirection penalty the book measures.
class PersonFullPimpl
{
public:
    PersonFullPimpl(std::string forename, std::string surname, std::string address,
                    std::string city, std::string country, std::string zip, int year)
        : m_impl{std::make_unique<Impl>(std::move(forename), std::move(surname),
                                        std::move(address), std::move(city),
                                        std::move(country), std::move(zip), year)}
    {
    }

    int yearOfBirth() const { return m_impl->year; } // one pointer hop to reach it

private:
    struct Impl
    {
        std::string forename;
        std::string surname;
        std::string address;
        std::string city;
        std::string country;
        std::string zip;
        int year;
    };
    std::unique_ptr<Impl> m_impl;
};

// ----- (c) Partial Bridge: hot data inline, cold data behind the pointer. ---
// forename, surname and year are read often, so they stay inline; the address
// block is read rarely, so it moves into Impl. The object is much smaller than
// PersonInline, and the hot loop never touches the cold pointer at all.
class PersonPartial
{
public:
    PersonPartial(std::string forename, std::string surname, std::string address,
                  std::string city, std::string country, std::string zip, int year)
        : m_forename{std::move(forename)}
        , m_surname{std::move(surname)}
        , m_year{year}
        , m_impl{std::make_unique<Impl>(std::move(address), std::move(city),
                                        std::move(country), std::move(zip))}
    {
    }

    int yearOfBirth() const { return m_year; } // hot member: direct, inline read

private:
    std::string m_forename; // hot
    std::string m_surname;  // hot
    int m_year;             // hot

    struct Impl
    {
        std::string address; // cold
        std::string city;    // cold
        std::string country; // cold
        std::string zip;     // cold
    };
    std::unique_ptr<Impl> m_impl; // cold data, not touched in the hot loop
};

namespace
{
// A padded string long enough to defeat the short-string optimization, so the
// strings behave like real heap-backed data rather than tiny inline buffers.
std::string makeText(std::mt19937& rng, const char* prefix)
{
    static const char* parts[] = {"alpha", "bravo", "charlie", "delta", "echo",
                                  "foxtrot", "golf", "hotel", "india", "juliet"};
    std::uniform_int_distribution<std::size_t> pick{0, 9};
    std::string s = prefix;
    s += parts[pick(rng)];
    s += '_';
    s += parts[pick(rng)];
    return s; // ~20+ chars: exceeds the SSO buffer, forces a heap allocation
}

// Build one vector of People, all three flavours from the same random seed so
// the data is identical and only the memory layout differs.
template <typename Person>
std::vector<Person> makePeople(std::size_t count)
{
    std::mt19937 rng{12345u}; // fixed seed: same data for every layout
    std::uniform_int_distribution<int> yearDist{1957, 2004};

    std::vector<Person> people;
    people.reserve(count);
    for (std::size_t i = 0; i < count; ++i)
    {
        people.emplace_back(makeText(rng, "fn_"), makeText(rng, "sn_"),
                            makeText(rng, "ad_"), makeText(rng, "ci_"),
                            makeText(rng, "co_"), makeText(rng, "zp_"),
                            yearDist(rng));
    }
    return people;
}

// Time "find the oldest person" repeated many times. Returns elapsed ms.
// A volatile-sourced bias is added to both sides of the comparison: it does not
// change the result, but it stops the optimizer from hoisting the (otherwise
// identical) min_element out of the loop, so we measure real repeated work.
template <typename Person>
double timeOldest(const std::vector<Person>& people, int repeats, long long& checksum)
{
    volatile int vbias = 0; // value is 0, but unknown to the optimizer
    using clock = std::chrono::steady_clock;

    const auto t0 = clock::now();
    for (int r = 0; r < repeats; ++r)
    {
        const int bias = vbias; // reloaded each iteration, prevents hoisting
        const auto it = std::min_element(
            people.begin(), people.end(),
            [bias](const Person& a, const Person& b)
            { return a.yearOfBirth() + bias < b.yearOfBirth() + bias; });
        checksum += it->yearOfBirth(); // also keeps the result alive
    }
    const auto t1 = clock::now();
    return std::chrono::duration<double, std::milli>(t1 - t0).count();
}
} // namespace

int main()
{
    // Enough elements to spill the CPU caches; modest repeats to keep it quick.
    constexpr std::size_t count = 25000;
    constexpr int repeats = 2000;

    std::cout << "Guideline 29 - Bridge performance: measure, do not guess\n";
    std::cout << "Elements: " << count << ", repeats: " << repeats << "\n\n";

    std::cout << "Object sizes (bytes):\n";
    std::cout << "  (a) PersonInline    : " << sizeof(PersonInline) << "\n";
    std::cout << "  (b) PersonFullPimpl : " << sizeof(PersonFullPimpl) << "\n";
    std::cout << "  (c) PersonPartial   : " << sizeof(PersonPartial) << "\n\n";

    const auto inlinePeople = makePeople<PersonInline>(count);
    const auto fullPeople = makePeople<PersonFullPimpl>(count);
    const auto partialPeople = makePeople<PersonPartial>(count);

    long long checksum = 0;
    const double tInline = timeOldest(inlinePeople, repeats, checksum);
    const double tFull = timeOldest(fullPeople, repeats, checksum);
    const double tPartial = timeOldest(partialPeople, repeats, checksum);

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Hot loop (find oldest) timings:\n";
    std::cout << "  (a) inline      : " << std::setw(9) << tInline << " ms"
              << "   (baseline 1.00x)\n";
    std::cout << "  (b) full Pimpl  : " << std::setw(9) << tFull << " ms"
              << "   (" << tFull / tInline << "x  - indirection penalty)\n";
    std::cout << "  (c) partial     : " << std::setw(9) << tPartial << " ms"
              << "   (" << tPartial / tInline << "x  - smaller hot object)\n\n";

    std::cout << "Expected shape of the result (it depends on the machine):\n";
    std::cout << "  full Pimpl  > 1.00x  (slower: every year read hops to heap)\n";
    std::cout << "  partial     < 1.00x  (faster: hot data inline, smaller stride)\n";
    std::cout << "Lower ratio is better. Always confirm with your own benchmark.\n";

    std::cout << "\n(checksum " << checksum << " - keeps the work from being optimized away)\n";
    return 0;
}
