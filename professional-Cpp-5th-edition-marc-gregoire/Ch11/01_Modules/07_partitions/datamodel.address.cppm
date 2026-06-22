/*
 * Chapter 11 - Modules (7/10): Address partition (interface)
 *
 * Interface for `datamodel:address`. Its implementation in
 * datamodel.address.cpp uses a subtly different declaration line - see
 * that file for the gotcha.
 */
export module datamodel:address;  // datamodel:address partition

export namespace DataModel
{
	class Address
	{
	public:
		Address();
	};
}
