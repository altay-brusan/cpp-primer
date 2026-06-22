/*
 * Chapter 10 - Covariant Return Types
 *
 * When a virtual function returns a pointer or reference to a base type, an
 * override is allowed to return a pointer/reference to a *more derived* type.
 * The compiler still treats it as overriding (so virtual dispatch works), but
 * callers that know the derived type get the more useful return type.
 *
 * Here `Car::getFilledUpPowerSource()` returns `PowerSource&`, but
 * `GasolineCar` returns `GasolinePowerSource&` and `ElectricalCar` returns
 * `ElectricalPowerSource&`. This is what lets the calls in main() reach the
 * concrete subclass type when they go through the concrete car.
 *
 * Key notes:
 *   - Covariance works for pointers and references, not for values.
 *   - The override declaration must still satisfy the rest of the signature
 *     (parameters, cv-qualifiers). Only the return type may be tightened.
 *   - The commented `PowerSource& getFilledUpPowerSource() override` lines are
 *     the *non*-covariant version - they would compile too but lose the
 *     derived type at the call site.
 *   - Use case: factory functions where the derived class can promise more
 *     than the base interface required.
 */
#include <print>

using namespace std;

class PowerSource
{
public:
	virtual ~PowerSource() = default;
	virtual void printType() = 0;
};

class GasolinePowerSource : public PowerSource
{
public:
	void printType() override { println("GasolinePowerSource"); }
	virtual void fillTank() { println("Gasoline tank filled up."); }
};

class ElectricalPowerSource : public PowerSource
{
public:
	void printType() override { println("ElectricalPowerSource"); }
	virtual void chargeBatteries() { println("Batteries charged."); }
};

class Car
{
public:
	virtual ~Car() = default;
	virtual PowerSource& getFilledUpPowerSource() = 0;
};

class GasolineCar : public Car
{
public:
	//PowerSource& getFilledUpPowerSource() override     // non-covariant, would also work
	GasolinePowerSource& getFilledUpPowerSource() override   // covariant - narrower return type
	{
		m_engine.fillTank();
		return m_engine;
	}
private:
	GasolinePowerSource m_engine;
};

class ElectricalCar : public Car
{
public:
	//PowerSource& getFilledUpPowerSource() override
	ElectricalPowerSource& getFilledUpPowerSource() override
	{
		m_engine.chargeBatteries();
		return m_engine;
	}
private:
	ElectricalPowerSource m_engine;
};

int main()
{
	GasolineCar gc;
	gc.getFilledUpPowerSource().printType();    // covariant: get GasolinePowerSource& directly

	println("");

	ElectricalCar ev;
	ev.getFilledUpPowerSource().printType();
}
