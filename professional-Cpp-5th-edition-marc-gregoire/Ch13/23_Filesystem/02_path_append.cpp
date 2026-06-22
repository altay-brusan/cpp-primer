/*
 * Chapter 13 - Filesystem: Appending Path Components
 *
 * append() and operator/= add a component to a path, automatically inserting a
 * platform-dependent directory separator. Contrast with the next sample
 * (concat / operator+=), which does NOT insert a separator.
 */

#include <print>
#include <filesystem>

using namespace std;
using namespace std::filesystem;

int main()
{
	path p{ "D:\\Foo" };
	p.append("Bar");
	p /= "Bar";
	println("{}", p.string());
}
