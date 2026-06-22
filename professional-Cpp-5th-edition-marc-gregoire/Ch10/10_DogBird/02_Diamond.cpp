/*
 * Chapter 10 - The Diamond Inheritance Problem
 *
 *           Animal (abstract)
 *           /     \
 *         Dog     Bird
 *           \     /
 *           DogBird
 *
 * Without virtual inheritance, DogBird would contain TWO Animal sub-objects
 * (one through Dog, one through Bird), and `Animal::eat()` is still ambiguous.
 * This sample sidesteps the duplication problem by *not* using `virtual` on
 * Animal and instead resolving the ambiguity with `using Dog::eat;` to pick
 * Dog's override as the one to keep.
 *
 * Key notes:
 *   - Animal has a pure virtual `eat()`, so it's abstract - you can't
 *     accidentally instantiate it.
 *   - `using Dog::eat;` makes Dog's eat() the unambiguous member of DogBird.
 *     Bird::eat() still exists but you have to qualify it to reach it.
 *   - The 20_VirtualBaseClasses sample shows the `virtual` inheritance fix
 *     that collapses the two Animal sub-objects into one.
 */
#include <print>

using namespace std;

class Animal
{
public:
	virtual ~Animal() = default;
	virtual void eat() = 0;
};

class Dog : public Animal
{
public:
	virtual void bark() { println("Woof!"); }
	void eat() override { println("The dog ate."); }
};

class Bird : public Animal
{
public:
	virtual void chirp() { println("Chirp!"); }
	void eat() override { println("The bird ate."); }
};

class DogBird : public Dog, public Bird
{
public:
	using Dog::eat;     // pick Dog's eat() as DogBird::eat()
};

int main()
{
	DogBird myConfusedAnimal;
	myConfusedAnimal.eat();   // "The dog ate." - the using-declaration picked Dog's
}
