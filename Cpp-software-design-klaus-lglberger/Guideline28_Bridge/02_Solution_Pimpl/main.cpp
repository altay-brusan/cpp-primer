/*
 * Guideline 28 - The Pimpl idiom (the simplest, nonpolymorphic Bridge)
 *
 * When a class has exactly ONE implementation and only needs to hide it, the
 * book reaches for the Pimpl idiom: the local, nonpolymorphic form of the
 * Bridge. All data members move into a private nested struct Impl that is only
 * DECLARED in the header; the class keeps a single std::unique_ptr<Impl>. The
 * definition of Impl lives in the source file, so adding, removing, or retyping
 * members no longer touches the header and no client recompiles - a compilation
 * firewall that also buys ABI stability (the class size stays one pointer).
 *
 * To keep this sample one translation unit, the header part and the source part
 * are marked with comments; in a real project the Impl definition and every
 * member body below the marker would live in Person.cpp.
 *
 * A famous wrinkle: a unique_ptr to an INCOMPLETE type cannot generate the
 * deleter. If the destructor were implicit it would be emitted in the header,
 * where Impl is incomplete, and fail to compile. So the destructor is declared
 * in the class and defined (= default) where Impl is complete. Copy must be
 * written by hand because unique_ptr is move-only, and a getter like
 * year_of_birth() cannot be inline in the header for the same incompleteness
 * reason.
 *
 * Key notes:
 *   - Forward-declared nested Impl plus unique_ptr<Impl> hides all members.
 *   - The destructor (and copy and the getter) must be defined where Impl is
 *     complete, never in the header - otherwise the incomplete type errors.
 *   - One implementation, no abstraction: this is Pimpl, not full Bridge.
 */
#include <iostream>
#include <memory>
#include <string>
#include <utility>

// ======================= <Person.h> ====================================
// Note: no <string> needed here in a real header; Impl is just forward declared
// so the postal-address strings stay an invisible implementation detail.
class Person
{
public:
    Person();
    ~Person(); // declared here, defined where Impl is complete

    Person(const Person& other);
    Person& operator=(const Person& other);

    Person(Person&& other) noexcept;
    Person& operator=(Person&& other) noexcept;

    void set(const std::string& forename, const std::string& surname, int year);
    int year_of_birth() const; // body must live where Impl is complete
    void print() const;

private:
    struct Impl;                       // declared, not defined
    std::unique_ptr<Impl> pimpl_;      // the pointer-to-implementation
};

// ======================= <Person.cpp> ==================================
// Everything below would live in the source file. Only here is Impl complete,
// so only here may its members be touched.
struct Person::Impl
{
    std::string forename;
    std::string surname;
    std::string address;
    std::string city;
    int year_of_birth = 0;
    // ... potentially many more data members, all hidden from clients
};

Person::Person() : pimpl_{std::make_unique<Impl>()} {}

// Defined here, where Impl is complete, so unique_ptr can build its deleter.
Person::~Person() = default;

Person::Person(const Person& other) : pimpl_{std::make_unique<Impl>(*other.pimpl_)} {}

Person& Person::operator=(const Person& other)
{
    *pimpl_ = *other.pimpl_;
    return *this;
}

Person::Person(Person&& other) noexcept = default;

Person& Person::operator=(Person&& other) noexcept = default;

void Person::set(const std::string& forename, const std::string& surname, int year)
{
    pimpl_->forename = forename;
    pimpl_->surname = surname;
    pimpl_->year_of_birth = year;
}

int Person::year_of_birth() const
{
    return pimpl_->year_of_birth; // legal only because Impl is complete here
}

void Person::print() const
{
    std::cout << pimpl_->forename << ' ' << pimpl_->surname
              << " (born " << pimpl_->year_of_birth << ")\n";
}

int main()
{
    Person p;
    p.set("Ada", "Lovelace", 1815);
    p.print();
    std::cout << "year_of_birth() = " << p.year_of_birth() << '\n';

    Person copy = p;            // hand-written copy: deep copy of the Impl
    Person moved = std::move(p); // move just transfers the pointer
    copy.print();
    moved.print();

    std::cout << "\nThe Person header only sees unique_ptr<Impl>; the address and\n"
                 "city members are an invisible implementation detail. Adding more\n"
                 "members to Impl recompiles only this file, never the clients.\n";
    return 0;
}
