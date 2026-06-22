/*
 * Chapter 13 - Filesystem: Constructing Paths
 *
 * std::filesystem::path (from <filesystem>) is the basic building block of the
 * filesystem library. A path can be absolute or relative and may include a
 * filename. This sample builds several paths and prints them; raw string
 * literals (R"(...)") avoid having to escape backslashes on Windows.
 *
 * Key notes:
 *   - A path is just text; it need not refer to anything that actually exists.
 *   - A path can be converted to the system's native format via c_str(),
 *     native(), or by streaming it.
 */

#include <print>
#include <filesystem>

using namespace std;
using namespace std::filesystem;

int main()
{
	path p1{ R"(D:\Foo\Bar)" };
	path p2{ "D:/Foo/Bar" };
	path p3{ "D:/Foo/Bar/MyFile.txt" };
	path p4{ R"(..\SomeFolder)" };
	path p5{ "/usr/lib/X11" };

	println("{}", p1.string());
	println("{}", p2.string());
	println("{}", p3.string());
	println("{}", p4.string());
	println("{}", p5.string());
}
