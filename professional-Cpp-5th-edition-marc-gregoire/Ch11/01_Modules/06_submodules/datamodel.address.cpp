/*
 * Chapter 11 - Modules (6/10): The address submodule (implementation)
 *
 * Implementation unit for the `datamodel.address` submodule. Notice the
 * `module datamodel.address;` line - same module name, no `export`, marks
 * this file as an implementation unit (not interface).
 */
module datamodel.address;

import std;

using namespace std;

DataModel::Address::Address()
{
	println("Address::Address()");
}
