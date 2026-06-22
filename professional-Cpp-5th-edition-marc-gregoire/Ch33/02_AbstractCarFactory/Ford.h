/*
 * Chapter 33 - Abstract Factory: the Ford Product Family
 *
 * Concrete products for the Abstract Factory example: FordSedan and FordSuv,
 * both deriving from a common Ford base which implements ICar. These are the
 * brand-specific objects that FordFactory instantiates, forming one coherent
 * family of related products.
 */

#pragma once

#include "ICar.h"
#include <string>

class Ford : public ICar
{
};

class FordSedan : public Ford
{
public:
	std::string info() const override { return "Ford Sedan"; }
};

class FordSuv : public Ford
{
public:
	std::string info() const override { return "Ford SUV"; }
};
