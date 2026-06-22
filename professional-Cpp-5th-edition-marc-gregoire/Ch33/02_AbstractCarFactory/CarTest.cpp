/*
 * Chapter 33 - Abstract Factory in Action
 *
 * Driver for the Abstract Factory pattern. The createSomeCars() helper takes an
 * ICarFactory& and builds a sedan and an SUV through the interface alone; it has
 * no idea whether it is talking to a Ford or a Toyota factory. main() passes a
 * FordFactory and then a ToyotaFactory to the same function, showing how an
 * entire family of related products is selected by swapping the factory.
 *
 * Key notes:
 *   - Contains main(); run as a standalone program.
 */

#include "FordFactory.h"
#include "ToyotaFactory.h"
#include <print>

using namespace std;

void createSomeCars(ICarFactory& carFactory)
{
	auto sedan{ carFactory.makeSedan() };
	auto suv{ carFactory.makeSuv() };
	println("Sedan: {}", sedan->info());
	println("SUV: {}", suv->info());
}

int main()
{
	FordFactory fordFactory;
	ToyotaFactory toyotaFactory;
	createSomeCars(fordFactory);
	createSomeCars(toyotaFactory);
}
