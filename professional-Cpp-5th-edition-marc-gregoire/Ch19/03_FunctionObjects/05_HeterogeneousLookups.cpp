/*
 * Chapter 19 - Heterogeneous Lookups with Transparent Comparators
 *
 * Demonstrates how transparent comparators enable heterogeneous lookup in associative
 * containers, avoiding temporary key construction. A plain set<string> forces a string to
 * be constructed (and memory allocated) when find() is called with a string literal or a
 * string_view. Switching to set<string, less<>> lets find() accept the literal or
 * string_view directly with no temporary. The third block applies the same idea to an
 * unordered_set using a custom Hasher that defines is_transparent = void together with
 * equal_to<> as the key-equality functor.
 *
 * Key notes:
 *   - is_transparent (here a void type alias) is what opts a comparator/hasher into
 *     heterogeneous lookup.
 *   - No main() output; the effects (avoided allocations) are conceptual.
 */
#include <set>
#include <unordered_set>
#include <string>
#include <string_view>
#include <functional>
#include <cstddef>

using namespace std;

class Hasher
{
public:
	using is_transparent = void;
	size_t operator()(string_view sv) const { return hash<string_view>{}(sv); }
};

int main()
{
	{
		set<string> mySet;
		auto i1{ mySet.find("Key") };       // string constructed, allocates memory!
		//auto i2 { mySet.find("Key"sv) };  // Compilation error!
	}

	{
		set<string, less<>> mySet;
		auto i1{ mySet.find("Key") };   // No string constructed, no memory allocated.
		auto i2{ mySet.find("Key"sv) }; // No string constructed, no memory allocated.
	}

	{
		unordered_set<string, Hasher, equal_to<>> mySet;
		auto i1{ mySet.find(string{ "Key" }) };   // No string constructed, no memory allocated.
		auto i2{ mySet.find("Key"sv) };           // No string constructed, no memory allocated.
	}
}