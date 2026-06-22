/*
 * Chapter 27 - A scoped_lock over an Array of Mutexes
 *
 * std::scoped_lock takes its mutexes as separate constructor arguments, so locking a
 * runtime-sized array of them needs help. This sample uses a variadic helper with
 * std::index_sequence to expand an array<mutex, N> into the individual arguments a
 * scoped_lock expects, locking all N mutexes at once. Structural example with no output.
 */

#include <mutex>
#include <array>
#include <utility>

using namespace std;

// Helper function to create the actual scoped_lock instance.
template<size_t N, size_t... Is>
auto make_scoped_lock(array<mutex, N>& mutexes, index_sequence<Is...>)
{
	return scoped_lock{ mutexes[Is]... };
}

// Helper function to make it easy to use.
template<size_t N>
auto make_scoped_lock(array<mutex, N>& mutexes)
{
	return make_scoped_lock(mutexes, make_index_sequence<N>{});
}

int main()
{
	array<std::mutex, 4> mutexes;

	auto lockAll{ make_scoped_lock(mutexes) };
}
