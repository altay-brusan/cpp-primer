/*
 * Chapter 32 - Mixin Classes via a Class Template
 *
 * Implements a mixin as a class template that derives from its own type parameter:
 * "template <typename T> class SelfDrivable : public T". This mixes the drive()
 * functionality into any existing class (Car, Truck) without modifying those classes,
 * producing SelfDrivable<Car> and SelfDrivable<Truck>. A mixin answers "what else can
 * this class do?" without committing to a full is-a relationship.
 *
 * Key notes:
 *   - Because SelfDrivable derives from T, drive() can call T's members (setSpeed()).
 */
#include <print>

using namespace std;

template <typename T>
class SelfDrivable : public T
{
public:
	void drive()
	{
		this->setSpeed(1.2);
	}
};

class Car
{
public:
	void setSpeed(double speed)
	{
		println("Car speed set to {}.", speed);
	}
};

class Truck
{
public:
	void setSpeed(double speed)
	{
		println("Truck speed set to {}.", speed);
	}
};

int main()
{
	SelfDrivable<Car> car;
	SelfDrivable<Truck> truck;
	car.drive();
	truck.drive();
}
