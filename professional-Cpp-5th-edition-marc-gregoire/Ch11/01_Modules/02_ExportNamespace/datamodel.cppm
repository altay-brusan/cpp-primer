/*
 * Chapter 11 - Modules (2/10): Exporting a Whole Namespace
 *
 * `export namespace DataModel { ... }` exports the namespace itself and
 * everything inside it. That's the easiest way to publish a coherent group
 * of types as a single unit.
 *
 * Key notes:
 *   - The qualified name on the importing side is `DataModel::Person`, etc.
 *   - Nothing is exported per-member; the `export` on the namespace covers
 *     all its members.
 *   - Compare with 03_ExportBlock, which exports an `export { ... }` block
 *     (a slightly different syntax with the same effect for this case).
 */
export module datamodel;

import std;

export namespace DataModel
{
	class Person { /* ... */ };

	class Address { /* ... */ };

	using Persons = std::vector<Person>;
}
