/*
 * Chapter 11 - Modules (7/10): Person partition
 *
 * The colon syntax `datamodel:person` says "this file is a partition of
 * module datamodel". The filename `datamodel.person.cppm` is just a
 * convention; only the `export module datamodel:person;` line matters to
 * the language.
 */
export module datamodel:person;  // datamodel:person partition

export namespace DataModel
{
	class Person { /* ... */ };
}
