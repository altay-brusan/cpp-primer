/*
 * Chapter 13 - Filesystem: Iterating Over Path Components
 *
 * A path is iterable: a range-based for loop visits each component in turn. For
 * "C:\Foo\Bar" on Windows the components are the root name "C:", the root
 * directory separator, "Foo", and "Bar".
 */

#include <print>
#include <filesystem>

using namespace std;
using namespace std::filesystem;

int main()
{
	path p{ R"(C:\Foo\Bar)" };
	for (const auto& component : p) {
		println("{}", component.string());
	}
}
