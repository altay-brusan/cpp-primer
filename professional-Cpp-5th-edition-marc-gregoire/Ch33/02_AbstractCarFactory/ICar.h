/*
 * Chapter 33 - Abstract Factory: the Product Interface
 *
 * Declares ICar, the abstract product type for the Abstract Factory example.
 * Concrete cars (Ford and Toyota sedans and SUVs) implement this interface, so
 * client code can work with any car through a single abstraction regardless of
 * which brand-specific factory produced it.
 */

#pragma once

#include <string>

class ICar
{
public:
	virtual ~ICar() = default;  // Always a virtual destructor!
	virtual std::string info() const = 0;
};
