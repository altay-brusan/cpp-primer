/*
 * Chapter 32 - Double Dispatch, Attempt 1: Brute Force
 *
 * First attempt at choosing behavior based on the run-time types of two objects: an
 * eats() method whose behavior depends on both the eater and the prey. Each Animal-derived
 * class implements eats() by explicitly querying the prey's run-time type with typeid.
 * This works for a few types but is criticized in the book: it is not object-oriented,
 * becomes repetitive as types grow, and does not force derived classes to handle new types.
 *
 * Key notes:
 *   - Virtual functions alone dispatch on only one object's run-time type, hence this hack.
 */
#include <print>
#include <typeinfo>

using namespace std;

class Animal
{
public:
	virtual bool eats(const Animal& prey) const = 0;
};

class Bear : public Animal
{
public:
	bool eats(const Animal& prey) const override;
};

class Fish : public Animal
{
public:
	bool eats(const Animal& prey) const override;
};

class TRex : public Animal
{
public:
	bool eats(const Animal& prey) const override;
};

bool Bear::eats(const Animal& prey) const
{
	if (typeid(prey) == typeid(Fish)) { return true; }
	return false;
}

bool Fish::eats(const Animal& prey) const
{
	if (typeid(prey) == typeid(Fish)) { return true; }
	return false;
}

bool TRex::eats(const Animal& /*prey*/) const
{
	return true;
} 

int main()
{
	Fish myFish;
	Bear myBear;
	TRex myDino;

	println("Fish eats bear? {}", myFish.eats(myBear));
	println("Fish eats dino? {}", myFish.eats(myDino));
	println("Dino eats bear? {}", myDino.eats(myBear));
	println("Bear eats fish? {}", myBear.eats(myFish));
}
