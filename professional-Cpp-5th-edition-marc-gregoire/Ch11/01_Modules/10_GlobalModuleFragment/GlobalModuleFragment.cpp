/*
 * Chapter 11 - Modules (10/10): Driver
 *
 * `import person;` brings in only the exports of the `person` module.
 * Anything `<cassert>` made available inside person.cppm stays there.
 */
import person;

int main()
{
	Person p;
}
