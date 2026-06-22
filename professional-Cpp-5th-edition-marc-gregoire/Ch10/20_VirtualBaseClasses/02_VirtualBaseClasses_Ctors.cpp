/*
 * Chapter 10 - Virtual Base Classes (2/2): Ctor Initialization Gotcha
 *
 * Surprising rule: when a class virtually inherits from a base, only the
 * *most-derived* class's constructor initializes the virtual base. Any
 * intermediate ctor-initializer mention of Animal is silently SKIPPED.
 *
 * The WRONG block at the top would lose Bella's weight: DogBird only calls
 * `Dog{weight, "Bella"}` and `Bird{weight, true}`, neither of which actually
 * initializes Animal because Animal is virtual. The default Animal() runs and
 * weight stays 0.
 *
 * The CORRECT block adds:
 *   - A protected name-only ctor on Dog: `Dog(string name)`. This is what
 *     intermediate constructors should use - they skip the Animal init.
 *   - DogBird's ctor calls `Animal{weight}` directly, plus the intermediate
 *     Dog/Bird ctors.
 *
 * Rule of thumb: any class that virtually inherits from V should have a
 * protected constructor that DOESN'T initialize V. The leaf class is in
 * charge of V.
 */
#include <print>
#include <string>

using namespace std;

// WRONG IMPLEMENTATION, LOSES VALUE OF WEIGHT.
//	class Animal
//	{
//	public:
//		explicit Animal(double weight) : m_weight{ weight } {}
//		virtual double getWeight() const { return m_weight; }
//	protected:
//		Animal() = default;
//	private:
//		double m_weight{ 0.0 };
//	};
//
//	class Dog : public virtual Animal
//	{
//	public:
//		explicit Dog(double weight, string name) : Animal{ weight }, m_name{ move(name) } {}
//	private:
//		string m_name;
//	};
//
//	class Bird : public virtual Animal
//	{
//	public:
//		explicit Bird(double weight, bool canFly) : Animal{ weight }, m_canFly{ canFly } {}
//	private:
//		bool m_canFly{ false };
//	};
//
//	class DogBird : public Dog, public Bird
//	{
//	public:
//		explicit DogBird(double weight, string name, bool canFly)
//			: Dog{ weight, move(name) }, Bird{ weight, canFly } {}     // never actually inits Animal!
//	};


// CORRECT IMPLEMENTATION.
class Animal
{
public:
	explicit Animal(double weight) : m_weight{ weight } {}
	virtual ~Animal() = default;
	virtual double getWeight() const { return m_weight; }
protected:
	Animal() = default;
private:
	double m_weight{ 0.0 };
};

class Dog : public virtual Animal
{
public:
	explicit Dog(double weight, string name) : Animal{ weight }, m_name{ move(name) } {}
protected:
	explicit Dog(string name) : m_name{ move(name) } {}   // intermediate ctor - skips Animal
private:
	string m_name;
};

class Bird : public virtual Animal
{
public:
	explicit Bird(double weight, bool canFly) : Animal{ weight }, m_canFly{ canFly } {}
protected:
	explicit Bird(bool canFly) : m_canFly{ canFly } {}
private:
	bool m_canFly{ false };
};

class DogBird : public Dog, public Bird
{
public:
	explicit DogBird(double weight, string name, bool canFly)
		: Animal { weight }, Dog{ move(name) }, Bird{ canFly } {}    // most-derived inits Animal
};

int main()
{
	DogBird dogBird{ 22.33, "Bella", true };
	println("Weight: {}", dogBird.getWeight());   // 22.33 - correctly preserved
}
