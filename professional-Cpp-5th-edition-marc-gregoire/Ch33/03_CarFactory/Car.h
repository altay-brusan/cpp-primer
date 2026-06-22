/*
 * Chapter 33 - Factory Method: the Product Hierarchy
 *
 * Declares the product types for the Factory Method example: the abstract ICar
 * interface and two concrete cars, Ford and Toyota. These are the objects that
 * the factory's overridable createCar() method will instantiate; the products
 * themselves stay simple so the focus is on how subclasses decide what to build.
 */

#pragma once

#include <string>

class ICar
{
public:
	virtual ~ICar() = default;  // Always a virtual destructor!
	virtual std::string info() const = 0;
};

class Ford : public ICar
{
public:
	std::string info() const override { return "Ford"; }
};

class Toyota : public ICar
{
public:
	std::string info() const override { return "Toyota"; }
};
