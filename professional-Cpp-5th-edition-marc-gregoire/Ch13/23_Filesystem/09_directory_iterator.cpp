/*
 * Chapter 13 - Filesystem: directory_iterator with Manual Recursion
 *
 * directory_iterator lists the contents of a single directory (non-recursive).
 * This sample produces the same tree printout as the recursive_directory_
 * iterator version, but does the recursion itself: when an entry is a directory,
 * printDirectoryStructure() calls itself with an increased indent level.
 *
 * Key notes:
 *   - Hard-coded to D:\Foo\Bar; exists() guards a missing path, so it prints
 *     nothing if that directory is absent.
 */

#include <print>
#include <filesystem>
#include <string>

using namespace std;
using namespace std::filesystem;

void printDirectoryStructure(const path& p, unsigned level = 0)
{
	if (!exists(p)) {
		return;
	}

	const string spacer(level * 2, ' ');

	if (is_regular_file(p)) {
		println("{}File: {} ({} bytes)", spacer, p.string(), file_size(p));
	} else if (is_directory(p)) {
		println("{}Dir: {}", spacer, p.string());
		for (auto& entry : directory_iterator{ p }) {
			printDirectoryStructure(entry, level + 1);
		}
	}
}

int main()
{
	path p{ R"(D:\Foo\Bar)" };
	printDirectoryStructure(p);
}
