/*
 * Chapter 32 - Double Dispatch, Attempt 2: Single Polymorphism with Overloading
 *
 * Second attempt: replace the if/else type checks with an overloaded eats() for each
 * concrete Animal type, declared pure virtual in the base. This solves only half the
 * problem - it is polymorphic on the eater (the receiving object) but not on the prey,
 * because overload resolution for the argument is decided at compile time. The commented
 * line in main() shows the case that fails to compile: eats() called with an Animal&.
 *
 * Key notes:
 *   - Overload resolution uses the compile-time type of the argument, not its run-time type.
 */
#include <print>


using namespace std;

// Forward declarations.
class Bear;
class Fish;
class TRex;

class Animal
{
public:
	virtual bool eats(const Bear&) const = 0;
	virtual bool eats(const Fish&) const = 0;
	virtual bool eats(const TRex&) const = 0;
};

class Bear : public Animal
{
public:
	bool eats(const Bear&) const override { return false; }
	bool eats(const Fish&) const override { return true; }
	bool eats(const TRex&) const override { return false; }
};

class Fish : public Animal
{
public:
	bool eats(const Bear&) const override { return false; }
	bool eats(const Fish&) const override { return true; }
	bool eats(const TRex&) const override { return false; }
};

class TRex : public Animal
{
public:
	bool eats(const Bear&) const override { return true; }
	bool eats(const Fish&) const override { return true; }
	bool eats(const TRex&) const override { return true; }
};

int main()
{
	Bear myBear;
	Fish myFish;
	println("Bear eats fish? {}", myBear.eats(myFish));

	{
		Animal& animalRef{ myBear };
		println("Bear eats fish? {}", animalRef.eats(myFish));
	}

	{
		Animal& animalRef{ myFish };
		//println("Bear eats fish? {}", myBear.eats(animalRef)); // BUG! No member function Bear::eats(Animal&)
	}
}
