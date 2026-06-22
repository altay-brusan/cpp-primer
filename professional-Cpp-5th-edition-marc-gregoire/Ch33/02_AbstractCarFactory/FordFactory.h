/*
 * Chapter 33 - Abstract Factory: the Ford Concrete Factory
 *
 * FordFactory is a concrete factory implementing ICarFactory. Its makeSedan and
 * makeSuv methods produce the Ford family of products (FordSedan, FordSuv),
 * returned as unique_ptr<ICar>. Selecting this factory commits the client to the
 * entire Ford family while the client code still only touches the interfaces.
 */

#pragma once

#include "ICarFactory.h"
#include "Ford.h"
#include <memory>

class FordFactory : public ICarFactory
{
public:
	std::unique_ptr<ICar> makeSuv() override { return std::make_unique<FordSuv>(); }
	std::unique_ptr<ICar> makeSedan() override { return std::make_unique<FordSedan>(); }
};
