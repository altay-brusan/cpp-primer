/*
 * Chapter 11 - Modules (1/10): Driver
 *
 * `import person;` brings in everything Person.cppm marked `export`. Notice
 * there is no `#include "Person.h"` - the build system resolves the named
 * module instead. Compilers find the .cppm by following their own search
 * rules (MSVC scans the source tree; Clang needs the precompiled .pcm).
 */
import person;
import std;

using namespace std;

int main()
{
	Person person{ "Kole", "Webb" };
	println("{}, {}", person.getLastName(), person.getFirstName());
}
