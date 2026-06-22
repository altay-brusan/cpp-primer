/*
 * Chapter 33 - Factory Method: the Factory Hierarchy
 *
 * Implements the Factory Method pattern. CarFactory provides a public
 * requestCar() template method that performs shared work (counting cars) and
 * delegates the actual object creation to a private virtual createCar() factory
 * method. Subclasses FordFactory and ToyotaFactory override createCar() to decide
 * which concrete product to instantiate, so the base class controls the process
 * while subclasses choose the product.
 *
 * Key notes:
 *   - requestCar() is the non-virtual "template method"; createCar() is the
 *     overridable factory method.
 *   - getNumberOfCarsProduced() exposes per-factory production statistics.
 */

#pragma once

#include "Car.h"
#include <memory>

class CarFactory
{
public:
	virtual ~CarFactory() = default;  // Always a virtual destructor!
	CarFactory() = default;
	CarFactory(const CarFactory&) = default;
	CarFactory& operator=(const CarFactory&) = default;
	CarFactory(CarFactory&&) = default;
	CarFactory& operator=(CarFactory&&) = default;
	
	std::unique_ptr<ICar> requestCar()
	{
		// Increment the number of cars produced and return the new car.
		++m_numberOfCarsProduced;
		return createCar();
	}

	unsigned getNumberOfCarsProduced() const
	{
		return m_numberOfCarsProduced;
	}

private:
	virtual std::unique_ptr<ICar> createCar() = 0;
	unsigned m_numberOfCarsProduced{ 0 };
};

class FordFactory final : public CarFactory
{
private:
	std::unique_ptr<ICar> createCar() override
	{
		return std::make_unique<Ford>();
	}
};

class ToyotaFactory final : public CarFactory
{
private:
	std::unique_ptr<ICar> createCar() override
	{
		return std::make_unique<Toyota>();
	}
};
