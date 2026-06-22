/*
 * Chapter 33 - Abstract Factory: the Factory Interface
 *
 * Declares ICarFactory, the abstract factory of the Abstract Factory pattern.
 * It defines operations to create a family of related products (makeSedan and
 * makeSuv) without specifying their concrete brand. Concrete factories such as
 * FordFactory and ToyotaFactory implement this interface so a whole product
 * family can be swapped by choosing a different factory.
 */

#pragma once

#include "ICar.h"
#include <memory>

class ICarFactory
{
public:
	virtual ~ICarFactory() = default;  // Always a virtual destructor!
	virtual std::unique_ptr<ICar> makeSuv() = 0;
	virtual std::unique_ptr<ICar> makeSedan() = 0;
};
