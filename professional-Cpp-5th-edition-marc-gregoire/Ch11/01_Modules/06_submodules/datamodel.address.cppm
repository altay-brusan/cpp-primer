/*
 * Chapter 11 - Modules (6/10): The address submodule (interface)
 *
 * Declares `DataModel::Address`. The implementation lives in
 * datamodel.address.cpp - same split as sample 04 but for a submodule.
 */
export module datamodel.address;  // datamodel.address submodule

export namespace DataModel
{
	class Address
	{
	public:
		Address();
	};
}
