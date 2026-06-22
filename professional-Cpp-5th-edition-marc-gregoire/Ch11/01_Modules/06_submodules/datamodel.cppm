/*
 * Chapter 11 - Modules (6/10): Submodules
 *
 * Submodules let you split a logical module into pieces with separate
 * names: `datamodel.person` and `datamodel.address`. Each is a full module
 * in its own right with its own .cppm.
 *
 * The umbrella module (`datamodel`) imports its submodules with
 * `export import` so consumers of `datamodel` get them transitively.
 *
 * Key notes:
 *   - The dot in `datamodel.person` is just part of the module name; there's
 *     no special "ownership" relationship enforced by the language. The
 *     pattern is purely a naming convention.
 *   - Compare with sample 07 (partitions), where the parts genuinely belong
 *     to the same module by language rule.
 */
export module datamodel;          // datamodel module

export import datamodel.person;   // Import and re-export the person submodule
export import datamodel.address;  // Import and re-export the address submodule

import std;

export namespace DataModel
{
	using Persons = std::vector<Person>;
}
