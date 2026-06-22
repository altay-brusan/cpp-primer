/*
 * Chapter 33 - Abstract Factory: the Toyota Product Family
 *
 * Concrete products for the Abstract Factory example: ToyotaSedan and ToyotaSuv,
 * both deriving from a common Toyota base which implements ICar. These mirror the
 * Ford family and are the objects produced by ToyotaFactory, demonstrating how a
 * second product family slots in behind the same ICar abstraction.
 */

#pragma once

#include "ICar.h"
#include <string>

class Toyota : public ICar
{
};

class ToyotaSedan : public Toyota
{
public:
	std::string info() const override { return "Toyota Sedan"; }
};

class ToyotaSuv : public Toyota
{
public:
	std::string info() const override { return "Toyota SUV"; }
};
