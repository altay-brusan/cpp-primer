/*
 * Chapter 11 - Modules (5/10): Driver
 *
 * Identical to sample 04's driver. The implementation layout in the .cppm
 * doesn't matter to the consumer.
 */
import person;
import std;

using namespace std;

int main()
{
	Person person{ "Kole", "Webb" };
	println("{}, {}", person.getLastName(), person.getFirstName());
}
