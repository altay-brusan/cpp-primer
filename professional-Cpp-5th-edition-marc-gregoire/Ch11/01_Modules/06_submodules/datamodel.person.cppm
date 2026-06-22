/*
 * Chapter 11 - Modules (6/10): The person submodule
 *
 * Standalone module that exports `DataModel::Person`. Could also be imported
 * directly by clients via `import datamodel.person;`.
 */
export module datamodel.person;  // datamodel.person submodule

export namespace DataModel
{
	class Person { /* ... */ };
}
