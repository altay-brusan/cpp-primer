/*
 * Chapter 32 - Double Dispatch, Attempt 3: The Double Dispatch Technique
 *
 * The truly polymorphic solution. Each Animal implements eats(prey) as a single line:
 * "return prey.eatenBy(*this);". Polymorphism fires twice - first to select the correct
 * eats() based on the eater's run-time type, then again on prey.eatenBy() to select the
 * correct overload based on the prey's run-time type. Because *this has a known concrete
 * type inside each derived eats(), the right eatenBy() overload can be resolved.
 *
 * Key notes:
 *   - eats() cannot be hoisted into the base class: there *this would be Animal, so the
 *     compiler could not pick the correct eatenBy() overload.
 *   - Forward declarations are needed because the base declares overloads taking the
 *     derived types by reference.
 */
#include <print>

using namespace std;

// Forward declarations.
class Fish;
class Bear;
class TRex;

class Animal
{
public:
	virtual bool eats(const Animal& prey) const = 0;

	virtual bool eatenBy(const Bear&) const = 0;
	virtual bool eatenBy(const Fish&) const = 0;
	virtual bool eatenBy(const TRex&) const = 0;
};

class Bear : public Animal
{
public:
	bool eats(const Animal& prey) const override { return prey.eatenBy(*this); }

	bool eatenBy(const Bear&) const override { return false; }
	bool eatenBy(const Fish&) const override { return false; }
	bool eatenBy(const TRex&) const override { return true; }
};

class Fish : public Animal
{
public:
	bool eats(const Animal& prey) const override { return prey.eatenBy(*this); }

	bool eatenBy(const Bear&) const override { return true; }
	bool eatenBy(const Fish&) const override { return true; }
	bool eatenBy(const TRex&) const override { return true; }
};

class TRex : public Animal
{
public:
	bool eats(const Animal& prey) const override { return prey.eatenBy(*this); }

	bool eatenBy(const Bear&) const override { return false; }
	bool eatenBy(const Fish&) const override { return false; }
	bool eatenBy(const TRex&) const override { return true; }
};


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
