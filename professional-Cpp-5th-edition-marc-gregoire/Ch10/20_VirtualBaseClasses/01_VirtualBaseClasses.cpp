/*
 * Chapter 10 - Virtual Base Classes (1/2): The Diamond Resolution
 *
 *            Animal (abstract)
 *            /     \
 *      virtual    virtual
 *           Dog    Bird
 *            \     /
 *            DogBird
 *
 * Without `virtual` inheritance, DogBird would have two Animal sub-objects
 * (one through Dog, one through Bird) and `sleep()` would be ambiguous. With
 * `virtual`, the two paths merge into a *single* Animal sub-object shared by
 * Dog and Bird. Member functions from Animal (like `sleep()`) are now
 * unambiguous.
 *
 * Key notes:
 *   - `class Dog : public virtual Animal` - the `virtual` here is at the
 *     inheritance point, not the function declaration. Easy to misread.
 *   - `eat()` is still ambiguous because Dog and Bird each override it; the
 *     DogBird::eat() override picks Dog's version with `Dog::eat();`.
 *   - Construction of a virtual base is the responsibility of the *most
 *     derived* class. See 02_VirtualBaseClasses_Ctors.cpp for the gotcha.
 *   - Virtual inheritance has measurable overhead (extra indirection to
 *     reach the shared base). Use it only when the diamond is unavoidable.
 */
#include <print>

using namespace std;

class Animal
{
public:
	virtual ~Animal() = default;
	virtual void eat() = 0;
	virtual void sleep() { println("zzzzz...."); }
};

class Dog : public virtual Animal
{
public:
	virtual void bark() { println("Woof!"); }
	void eat() override { println("The dog ate."); }
};

class Bird : public virtual Animal
{
public:
	virtual void chirp() { println("Chirp!"); }
	void eat() override { println("The bird ate."); }
};

class DogBird : public Dog, public Bird
{
public:
	void eat() override { Dog::eat(); }   // still has to disambiguate eat()
};

int main()
{
	DogBird myConfusedAnimal;
	myConfusedAnimal.sleep();  // Unambiguous: virtual inheritance merged the two Animal sub-objects.
}
