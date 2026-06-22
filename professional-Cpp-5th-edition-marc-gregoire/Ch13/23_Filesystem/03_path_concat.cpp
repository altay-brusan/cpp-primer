/*
 * Chapter 13 - Filesystem: Concatenating onto a Path
 *
 * concat() and operator+= append text directly to a path WITHOUT inserting any
 * separator (so "D:\Foo" + "Bar" + "Bar" yields "D:\FooBarBar"). This is the
 * counterpart to the append() / operator/= sample.
 */

#include <print>
#include <filesystem>

using namespace std;
using namespace std::filesystem;

int main()
{
	path p{ "D:\\Foo" };
	p.concat("Bar");
	p += "Bar";
	println("{}", p.string());
}
