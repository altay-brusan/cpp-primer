/*
 * Chapter 13 - Filesystem: Decomposing a Path
 *
 * The path interface offers many accessors for breaking a path apart. This
 * sample uses root_name(), filename(), stem(), and extension() to pull the
 * pieces out of "C:\Foo\Bar\file.txt". Others include parent_path(),
 * replace_extension(), is_absolute(), and more.
 */

#include <print>
#include <filesystem>

using namespace std;
using namespace std::filesystem;

int main()
{
	path p{ R"(C:\Foo\Bar\file.txt)" };
	println("{}", p.root_name().string());
	println("{}", p.filename().string());
	println("{}", p.stem().string());
	println("{}", p.extension().string());
}