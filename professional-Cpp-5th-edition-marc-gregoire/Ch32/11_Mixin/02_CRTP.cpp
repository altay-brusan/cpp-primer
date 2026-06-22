/*
 * Chapter 32 - Mixin Classes via the Curiously Recurring Template Pattern (CRTP)
 *
 * A variation where the relationship is inverted: each concrete class derives from the
 * mixin template instantiated with itself, for example "class Car : public
 * SelfDrivable<Car>". The mixin's drive() then static_casts *this down to Derived& to
 * call the derived class's members. This is static (compile-time) polymorphism, with no
 * virtual function overhead.
 *
 * Key notes:
 *   - "Curiously recurring" refers to a class naming itself as the template argument of
 *     its own base class.
 */
#include <print>

using namespace std;

template <typename Derived>
class SelfDrivable
{
public:
	void drive()
	{
		auto& self{ static_cast<Derived&>(*this) };
		self.setSpeed(1.2);
	}
};

class Car : public SelfDrivable<Car>
{
public:
	void setSpeed(double speed)
	{
		println("Car speed set to {}.", speed);
	}
};

class Truck : public SelfDrivable<Truck>
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
