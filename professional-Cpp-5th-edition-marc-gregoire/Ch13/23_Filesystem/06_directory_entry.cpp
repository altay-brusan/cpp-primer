/*
 * Chapter 13 - Filesystem: Querying with directory_entry
 *
 * A path is only text; to query an actual file or directory on disk you
 * construct a directory_entry from it. Its interface includes exists(),
 * is_directory(), is_regular_file(), file_size(), and last_write_time(). Here
 * it reports the size of win.ini if that file exists and is a regular file.
 *
 * Key notes:
 *   - The hard-coded path c:/windows/win.ini is Windows-specific and may not be
 *     present; the exists()/is_regular_file() guard keeps it safe.
 */

#include <print>
#include <filesystem>

using namespace std;
using namespace std::filesystem;

int main()
{
	path myPath{ "c:/windows/win.ini" };
	directory_entry dirEntry{ myPath };
	if (dirEntry.exists() && dirEntry.is_regular_file()) {
		println("File size: {}", dirEntry.file_size());
	}
}
