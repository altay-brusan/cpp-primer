/*
 * Chapter 16 - Bit Manipulation Utilities from <bit>
 *
 * Part of the Standard Library tour: this sample demonstrates the C++20 bit
 * functions in <bit>, all of which take an unsigned integral type. It shows
 * popcount() (count of set bits), countl_one()/countr_one() (consecutive one
 * bits from the left/right), rotl() (bit rotation), and bit_ceil()/bit_floor()
 * (nearest powers of two). It also uses the C++23 std::byteswap() to reverse the
 * byte order of a uint32_t, and uses std::println with the {:08b} binary format.
 *
 * Key notes:
 *   - These functions replace hand-rolled bit-twiddling and document intent clearly.
 *   - byteswap() is C++23; the other functions are C++20.
 */

#include <print>
#include <bit>
#include <cstdint>

using namespace std;

int main()
{
	println("{}", popcount(0b10101010u)); // 4

	uint8_t value{ 0b11101011u };
	println("{}", countl_one(value));     // 3
	println("{}", countr_one(value));     // 2

	value = 0b10001000u;
	println("{:08b}", rotl(value, 2));    // 00100010

	value = 0b00001011u;
	println("bit_ceil({0:08b} = {0}) = {1:08b} = {1}",
		value, bit_ceil(value));          // bit_ceil(00001011 = 11) = 00010000 = 16
	println("bit_floor({0:08b} = {0}) = {1:08b} = {1}",
		value, bit_floor(value));         // bit_floor(00001011 = 11) = 00001000 = 8

	uint32_t before{ 0x12345678u };
	println("{:x}", before);              // 12345678
	uint32_t after{ byteswap(before) };   // C++23 std::byteswap().
	println("{:x}", after);               // 78563412
}
