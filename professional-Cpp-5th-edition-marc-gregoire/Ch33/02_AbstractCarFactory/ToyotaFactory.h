/*
 * Chapter 33 - Abstract Factory: the Toyota Concrete Factory
 *
 * ToyotaFactory is a concrete factory implementing ICarFactory, producing the
 * Toyota family of products (ToyotaSedan, ToyotaSuv) as unique_ptr<ICar>. It is
 * interchangeable with FordFactory: client code that holds an ICarFactory&
 * gets a consistent Toyota family without knowing the concrete types involved.
 */

#pragma once

#include "ICarFactory.h"
#include "Toyota.h"
#include <memory>

class ToyotaFactory : public ICarFactory
{
public:
	std::unique_ptr<ICar> makeSuv() override { return std::make_unique<ToyotaSuv>(); }
	std::unique_ptr<ICar> makeSedan() override { return std::make_unique<ToyotaSedan>(); }
};
