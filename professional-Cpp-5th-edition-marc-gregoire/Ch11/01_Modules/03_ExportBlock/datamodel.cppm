/*
 * Chapter 11 - Modules (3/10): Export Block
 *
 * `export { ... }` exports every declaration inside the braces. It's the most
 * flexible form when you want to publish several unrelated declarations at
 * once without sprinkling `export` on each one.
 *
 * Key notes:
 *   - The block can contain anything you could declare at file scope -
 *     classes, functions, variables, type aliases, namespaces.
 *   - Equivalent end result to sample 02 for this particular example, but the
 *     block form is friendlier when the namespace isn't the only thing being
 *     exported.
 */
export module datamodel;

import std;

export
{
	namespace DataModel
	{
		class Person { /* ... */ };

		class Address { /* ... */ };

		using Persons = std::vector<Person>;
	}
}
