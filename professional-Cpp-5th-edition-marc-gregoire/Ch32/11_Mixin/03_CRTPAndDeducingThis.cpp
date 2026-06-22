/*
 * Chapter 32 - Mixin Classes with a Deducing-this Member Function
 *
 * Achieves the same static-polymorphism mixin as the CRTP sample, but without making
 * SelfDrivable a template. The C++23 explicit object parameter ("this auto& self") lets
 * drive() deduce the concrete derived type at the call site, so self.setSpeed() resolves
 * to Car::setSpeed() or Truck::setSpeed() directly - no template parameter and no
 * static_cast needed.
 *
 * Key notes:
 *   - Deducing this is a C++23 feature; "this auto& self" replaces the implicit this.
 */
#include <print>

using namespace std;

class SelfDrivable
{
public:
	void drive(this auto& self)
	{
		self.setSpeed(1.2);
	}
};

class Car : public SelfDrivable
{
public:
	void setSpeed(double speed)
	{
		println("Car speed set to {}.", speed);
	}
};

class Truck : public SelfDrivable
{
public:
	void setSpeed(double speed)
	{
		println("Truck speed set to {}.", speed);
	}
};

int main()
{
	Car car;
	Truck truck;
	car.drive();
	truck.drive();
}
