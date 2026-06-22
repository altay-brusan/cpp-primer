/*
 * Chapter 10 - Multiple Inheritance (the ambiguity problem)
 *
 * DogBird inherits from two unrelated classes that both define `eat()`. The
 * call `myConfusedAnimal.eat()` is ambiguous - there are two equally good
 * candidates with no rule to pick one. Two ways to disambiguate are shown:
 *
 *   1. Cast first: `dynamic_cast<Dog&>(...)` selects Dog's view of the object,
 *      then `eat()` resolves to Dog::eat().
 *   2. Qualified call: `myConfusedAnimal.Dog::eat()` names the exact source.
 *
 * Two ways to make `eat()` non-ambiguous on the class itself (commented out so
 * the program still compiles to demonstrate the ambiguity):
 *
 *   - Override `eat()` in DogBird and explicitly call the chosen base.
 *   - `using Dog::eat;` to pull the chosen base version into DogBird's scope.
 *
 * The Diamond version (02_Diamond.cpp) introduces a common base and shows
 * `virtual` inheritance.
 */
#include <print>

using namespace std;

class Dog
{
public:
	virtual void bark() { println("Woof!"); }
	virtual void eat() { println("The dog ate."); }
};

class Bird
{
public:
	virtual void chirp() { println("Chirp!"); }
	virtual void eat() { println("The bird ate."); }
};

class DogBird : public Dog, public Bird
{
public:
	// Uncomment ONE to remove the ambiguity:
	//void eat() override
	//{
	//	Dog::eat();          // Explicitly call Dog's version of eat()
	//}

	//using Dog::eat;        // Explicitly inherit Dog's version of eat()
};

int main()
{
	DogBird myConfusedAnimal;

	myConfusedAnimal.bark();                       // unique to Dog
	myConfusedAnimal.chirp();                      // unique to Bird
	//myConfusedAnimal.eat();                      // Error! Ambiguous.
	dynamic_cast<Dog&>(myConfusedAnimal).eat();    // Calls Dog::eat() via view of the Dog sub-object
	myConfusedAnimal.Dog::eat();                   // Calls Dog::eat() by explicit qualifier
}
