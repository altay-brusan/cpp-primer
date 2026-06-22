/*
 * Chapter 11 - Modules (2/10): Driver for the namespace-exported module
 *
 * Only the namespace was exported - clients see DataModel::Person etc.
 * directly, with no extra `using` needed.
 */
import datamodel;

int main()
{
	DataModel::Person p;
	DataModel::Address a;
	DataModel::Persons persons;
}
