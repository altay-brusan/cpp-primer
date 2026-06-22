/*
 * Chapter 11 - Modules (7/10): Address partition (implementation)
 *
 * Surprise: an *implementation unit* attached to a partition still says
 * `module datamodel;`, not `module datamodel:address;`. The implementation
 * unit belongs to the whole module, not to the partition.
 *
 * The corresponding interface unit (datamodel.address.cppm) is what says
 * `export module datamodel:address;` - that's where the partition identity
 * lives.
 */
module datamodel;  // Not datamodel:address!

import std;

using namespace std;

DataModel::Address::Address()
{
	println("Address::Address()");
}
