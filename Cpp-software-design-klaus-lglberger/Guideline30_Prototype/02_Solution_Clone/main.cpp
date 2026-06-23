/*
 * Guideline 30 - The solution: the PROTOTYPE design pattern, a virtual clone.
 *
 * Intent (Gang of Four): "Specify the kind of objects to create using a
 * prototypical instance, and create new objects by copying this prototype."
 * In C++ this is a virtual clone function in the base class. Through it anyone
 * holding only a pointer-to-base can ask a prototype for an exact copy of
 * itself, without ever knowing the concrete type (Sheep, Dog, or anything
 * added later - an OPEN set of types).
 *
 * Each derived class overrides clone to copy-construct itself and hand back a
 * std::unique_ptr to base. By reusing its own copy constructor inside clone,
 * the class stays correct even as it gains new members (the DRY principle).
 * The special member functions are left intact: clone merely ADDS a way to
 * copy - virtual copying - on top of normal value copying.
 *
 * Key notes:
 *   - clone is pure virtual: every concrete animal must say how to copy itself,
 *     and (per the LSP) must return a faithful copy of its own dynamic type.
 *   - The return type std::unique_ptr to Animal gives the caller ownership with
 *     automatic cleanup; no manual delete, no slicing.
 *   - Cloning a std::vector of base pointers reproduces each element's true
 *     dynamic type and state - the herd stays a herd of real sheep and dogs.
 *   - This is a reference-semantics pattern: it pays for pointer indirection and
 *     a heap allocation per copy. That is the price of an abstract copy.
 */
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

// Abstract base: a virtual clone is the Prototype hook for abstract copying.
class Animal
{
public:
    virtual ~Animal() = default;
    virtual void makeSound() const = 0;
    virtual std::unique_ptr<Animal> clone() const = 0; // Prototype pattern

protected:
    explicit Animal(std::string name) : m_name(std::move(name)) {}
    const std::string& name() const { return m_name; }

private:
    std::string m_name;
};

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

    // Reuse our own copy constructor; correct even if Sheep gains new members.
    std::unique_ptr<Animal> clone() const override
    {
        return std::make_unique<Sheep>(*this);
    }

private:
    std::string m_wool;
};

class Dog : public Animal
{
public:
    Dog(std::string name, int tricks)
        : Animal(std::move(name)), m_tricks(tricks)
    {
    }

    void makeSound() const override
    {
        std::cout << name() << " the dog (" << m_tricks << " tricks): woof\n";
    }

    std::unique_ptr<Animal> clone() const override
    {
        return std::make_unique<Dog>(*this);
    }

private:
    int m_tricks;
};

int main()
{
    // We hold only pointers-to-base, yet we get exact copies via clone.
    std::unique_ptr<Animal> prototype = std::make_unique<Sheep>("Dolly", "white");

    std::cout << "Prototype and its clone sound identical:\n";
    prototype->makeSound();
    std::unique_ptr<Animal> twin = prototype->clone();
    twin->makeSound(); // dynamic type and state preserved

    // Copy a whole herd of base pointers: every element keeps its real type.
    std::vector<std::unique_ptr<Animal>> herd;
    herd.push_back(std::make_unique<Sheep>("Molly", "black"));
    herd.push_back(std::make_unique<Dog>("Rex", 3));
    herd.push_back(std::make_unique<Sheep>("Shaun", "grey"));

    std::vector<std::unique_ptr<Animal>> copy;
    copy.reserve(herd.size());
    for (const std::unique_ptr<Animal>& a : herd)
        copy.push_back(a->clone()); // abstract copy through the base

    std::cout << "\nDeep-copied herd - each clone kept its dynamic type:\n";
    for (const std::unique_ptr<Animal>& a : copy)
        a->makeSound();

    std::cout << "\nclone() gave us exact copies through Animal pointers alone,\n"
                 "with no slicing and no knowledge of the concrete types.\n";
    return 0;
}
