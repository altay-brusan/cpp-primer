/*
 * Chapter 11 - Modules (6/10): Driver
 *
 * Imports just `datamodel.address` directly - submodules are independently
 * importable. To get everything through the umbrella, `import datamodel;`
 * would work too thanks to the re-exports in datamodel.cppm.
 */
import datamodel.address;

int main()
{
	DataModel::Address a;
}
