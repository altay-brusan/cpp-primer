/*
 * Chapter 13 - Filesystem: Querying Free Space
 *
 * One of the filesystem helper functions: space() returns a space_info struct
 * describing a filesystem's capacity and free space. This sample prints the
 * capacity and free bytes of the C: drive.
 *
 * Key notes:
 *   - The "c:\\" argument is Windows-specific; use an appropriate path on other
 *     platforms.
 */

#include <print>
#include <filesystem>

using namespace std;
using namespace std::filesystem;

int main()
{
	space_info s{ space("c:\\") };
	println("Capacity: {}", s.capacity);
	println("Free: {}", s.free);
}
