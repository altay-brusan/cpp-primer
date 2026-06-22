/*
 * Chapter 10 - C++ Casts (3/4): std::bit_cast (C++20)
 *
 * `std::bit_cast<Dest>(src)` interprets the underlying bits of `src` as a
 * `Dest`, with both types having the same size. Unlike reinterpret_cast it
 * actually *copies* the bytes into a fresh Dest object, so it doesn't
 * violate strict aliasing.
 *
 * This is the modern, safe way to do the classic "view this float as an
 * int" trick - often used in numeric code (NaN detection, hashing) and in
 * serialization.
 *
 * Key notes:
 *   - Both types must be `TriviallyCopyable` and the same size.
 *   - `constexpr` in C++20, so it can run at compile time.
 *   - For pointer-to-int round trips, use reinterpret_cast or
 *     `std::intptr_t`, not bit_cast.
 */
#include <print>
#include <bit>

using namespace std;

int main()
{
	float asFloat{ 1.23f };
	auto asUint{ bit_cast<unsigned int>(asFloat) };       // safely view the bit pattern as unsigned int
	if (bit_cast<float>(asUint) == asFloat) {             // round-trip back to float
		println("Roundtrip success.");
	}
}
