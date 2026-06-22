/*
 * Chapter 11 - Modules (4/10): Driver
 *
 * Same client code as sample 01. Splitting the implementation into a .cpp
 * is invisible to importers.
 */
import person;
import std;

using namespace std;

int main()
{
	Person person{ "Kole", "Webb" };
	println("{}, {}", person.getLastName(), person.getFirstName());
}
