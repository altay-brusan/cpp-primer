/*
 * Chapter 18 - map::merge()
 *
 * merge() moves all nodes from a source map into a destination map. Nodes whose
 * keys would duplicate an existing key in the destination cannot be moved and
 * are left behind in the source, as shown by the leftover {2, 22} element.
 */

#include <print>
#include <map>

using namespace std;

int main()
{
	map<int, int> src{ { 1, 11 },{ 2, 22 } };
	map<int, int> dst{ { 2, 22 },{ 3, 33 },{ 4, 44 },{ 5, 55 } };
	dst.merge(src);
	println("src = {}", src);
	println("dst = {}", dst);
}
