/*
 * Guideline 30 - The problem: copying a polymorphic object through a base
 *                type SLICES it (the symptom Prototype exists to cure).
 *
 * The book's scenario: you hold only a pointer-to-base (an Animal pointer) and
 * you want an exact copy of whatever animal it really refers to. The obvious
 * move is to dereference and copy: "Animal duplicate = somePtr;". But the copy
 * constructor invoked is Animal's own; it copies only the Animal part and
 * discards everything the derived Sheep added. That is slicing. The result is
 * a real, well-defined Animal value - the program compiles and runs - but the
 * dynamic type is gone and the derived data is lost.
 *
 * Note the base here is intentionally CONCRETE (makeSound is virtual but not
 * pure). That is what lets the slicing copy compile at all, so we can watch the
 * loss happen. With an abstract base you could not even form an Animal value;
 * the copy would simply be unavailable, which is a different failure.
 *
 * Key notes:
 *   - Slicing is lossy, not undefined: the sliced value is a valid base object.
 *   - A virtual call on the sliced value resolves to the BASE override, because
 *     the static and dynamic type are now both Animal. The Sheep behavior and
 *     the Sheep state (its wool color) are gone.
 *   - Storing copies in a std::vector of base VALUES has the same effect: every
 *     element is sliced down to Animal, so the herd forgets it was sheep.
 *   - The fix is an abstract copy operation, a virtual clone, shown in 02.
 */
#include <iostream>
#include <string>
#include <utility>
#include <vector>

// Concrete base so that copying an Animal VALUE is allowed (and thus sliceable).
class Animal
{
public:
    explicit Animal(std::string name) : m_name(std::move(name)) {}
    virtual ~Animal() = default;

    virtual void makeSound() const
    {
        std::cout << m_name << ": (some generic animal noise)\n";
    }

    const std::string& name() const { return m_name; }

private:
    std::string m_name;
};

// A Sheep adds its own state (wool color) and its own sound.
class Sheep : public Animal
{
public:
    Sheep(std::string name, std::string wool)
        : Animal(std::move(name)), m_wool(std::move(wool))
    {
    }

    void makeSound() const override
    {
        std::cout << name() << " the " << m_wool << " sheep: baa\n";
    }

private:
    std::string m_wool;
};

int main()
{
    std::cout << "Original, accessed through a base pointer:\n";
    Sheep dolly{"Dolly", "white"};
    const Animal* prototype = &dolly; // all we have is a pointer-to-base
    prototype->makeSound();           // virtual dispatch -> Sheep::makeSound

    // We want a copy, but we only know the static type Animal. Copying the
    // dereferenced object invokes Animal's copy constructor: it copies the
    // Animal sub-object and silently drops the Sheep part.
    std::cout << "\nNaive copy through the base value (SLICED):\n";
    Animal sliced = *prototype;
    sliced.makeSound(); // now resolves to Animal::makeSound - the sheep is gone

    // The same loss happens when we try to keep copies in a container of values.
    std::cout << "\nA herd stored as base VALUES is sliced on insertion:\n";
    std::vector<Animal> herd;
    herd.push_back(*prototype); // sliced copy
    herd.push_back(Sheep{"Molly", "black"}); // sliced on the way in
    for (const Animal& a : herd)
        a.makeSound(); // every element behaves as a plain Animal

    std::cout << "\nSlicing compiled and ran, but each copy lost its dynamic\n"
                 "type and its derived state. Guideline 30 fixes this with a\n"
                 "virtual clone (see 02_Solution_Clone).\n";
    return 0;
}
