/*
 * Chapter 11 - Modules (7/10): Module Partitions
 *
 * Partitions are pieces of the SAME named module, identified by a colon:
 * `datamodel:person`, `datamodel:address`. The umbrella .cppm imports them
 * with `:partition-name` and re-exports them with `export import :name;`.
 *
 * Differences vs. submodules (sample 06):
 *   - Partitions are not importable from outside; clients always import the
 *     primary module name (`datamodel`).
 *   - Partitions share the same module identity, so they can see each
 *     other's non-exported declarations.
 *   - The umbrella module is mandatory: there is no way to import a
 *     partition standalone.
 *
 * Key notes:
 *   - Use partitions when the pieces are logically one module but you want
 *     to split the source files. Use submodules when consumers genuinely
 *     might want to import only one piece.
 */
export module datamodel; // datamodel module (primary module interface file)

export import :person;   // Import and re-export the person partition
export import :address;  // Import and re-export the address partition

import std;

export namespace DataModel
{
	using Persons = std::vector<Person>;
}
