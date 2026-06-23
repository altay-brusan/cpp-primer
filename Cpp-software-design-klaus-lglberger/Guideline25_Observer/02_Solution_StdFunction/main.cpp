/*
 * Guideline 25 - Apply Observers as an Abstract Notification Mechanism
 *                (a value semantics, std::function based Observer)
 *
 * Concern: the classic Observer forces every reaction into a class that derives
 * from the Observer base and overrides update() in one fixed way. That is
 * intrusive. Following the book's value semantics direction, we replace the
 * inheritance hierarchy with COMPOSITION: the Observer stores a std::function
 * holding the update logic. Now the reaction can be a free function, a lambda,
 * or any callable with the right signature, and the implementer is free to make
 * it stateless or stateful without inheriting from anything.
 *
 * Grounding in the book:
 *   - Observer becomes an ADAPTER over std::function. It still earns its keep:
 *     std::function is value semantic and likes to be copied or moved, but we do
 *     NOT want a COPY of a (possibly stateful) observer to be the one notified.
 *     Wrapping it in an Observer object that we refer to by a stable address
 *     avoids that, and gives a stable unique handle for attach plus detach.
 *   - The subject still stores observers as RAW POINTERS (a non owning unique
 *     handle), exactly as in the classic version: there is no fully value based
 *     observer because the address is the easiest unique identifier.
 *   - This std::function form fits a PULL observer with a SINGLE update()
 *     function. A push observer with several update() overloads cannot be a
 *     single std::function; for that the book points to Type Erasure.
 *
 * Key notes:
 *   - OnUpdate is the agreed signature: void(const Subject and, StateTag). Any
 *     callable matching it can be an observer; no base class is needed.
 *   - nameObserver is built from a FREE function (reusable, class free); the
 *     addressObserver is built from a stateful LAMBDA that counts moves.
 *   - Observer has NO virtual functions and NO virtual destructor: behavior is
 *     composed in, not inherited.
 *   - Lifetime is still the caller's job: the Observer objects must outlive
 *     their registration, because the subject only borrows their addresses.
 */
#include <functional>
#include <iostream>
#include <set>
#include <string>
#include <utility>

// Value based Observer: an Adapter that holds the update logic as a callable
// instead of demanding inheritance. No virtual functions are involved.
template <typename Subject, typename StateTag>
class Observer
{
public:
    using OnUpdate = std::function<void(const Subject&, StateTag)>;

    explicit Observer(OnUpdate onUpdate) : m_onUpdate(std::move(onUpdate))
    {
        // A real program could reject an empty std::function here.
    }

    // Non virtual: just forward the call to the stored callable.
    void update(const Subject& subject, StateTag property)
    {
        m_onUpdate(subject, property);
    }

private:
    OnUpdate m_onUpdate;
};

// The same subject as the classic version; nothing about it changes.
class Person
{
public:
    enum StateChange
    {
        forenameChanged,
        surnameChanged,
        addressChanged
    };

    using PersonObserver = Observer<Person, StateChange>;

    Person(std::string forename, std::string surname)
        : m_forename(std::move(forename)), m_surname(std::move(surname))
    {
    }

    bool attach(PersonObserver* observer)
    {
        auto [pos, success] = m_observers.insert(observer);
        (void)pos;
        return success;
    }

    bool detach(PersonObserver* observer)
    {
        return m_observers.erase(observer) > 0U;
    }

    void forename(std::string value)
    {
        m_forename = std::move(value);
        notify(forenameChanged);
    }
    void surname(std::string value)
    {
        m_surname = std::move(value);
        notify(surnameChanged);
    }
    void address(std::string value)
    {
        m_address = std::move(value);
        notify(addressChanged);
    }

    const std::string& forename() const { return m_forename; }
    const std::string& surname() const { return m_surname; }
    const std::string& address() const { return m_address; }

private:
    void notify(StateChange property)
    {
        for (auto it = m_observers.begin(); it != m_observers.end();)
        {
            auto const pos = it++;
            (*pos)->update(*this, property);
        }
    }

    std::string m_forename;
    std::string m_surname;
    std::string m_address;
    std::set<PersonObserver*> m_observers; // non owning handles
};

// A reaction expressed as a plain FREE function: not bound to any class, so it
// is easy to reuse. It pulls what it needs and filters on the tag.
void onNameChanged(const Person& person, Person::StateChange property)
{
    if (property == Person::forenameChanged || property == Person::surnameChanged)
    {
        std::cout << "[name ] now: " << person.forename() << ' '
                  << person.surname() << '\n';
    }
}

int main()
{
    using PersonObserver = Observer<Person, Person::StateChange>;

    // Observer 1: composed from a free function.
    PersonObserver nameObserver(onNameChanged);

    // Observer 2: composed from a STATEFUL lambda that captures a counter,
    // showing how the std::function form supports per observer state with no
    // class boilerplate.
    int moves = 0;
    PersonObserver addressObserver(
        [&moves](const Person& person, Person::StateChange property)
        {
            if (property == Person::addressChanged)
            {
                ++moves;
                std::cout << "[addr ] move #" << moves << ": " << person.forename()
                          << " -> " << person.address() << '\n';
            }
        });

    Person homer("Homer", "Simpson");
    Person marge("Marge", "Simpson");

    homer.attach(&nameObserver);
    homer.attach(&addressObserver);
    marge.attach(&addressObserver);

    std::cout << "std::function observers (free function plus stateful lambda):\n";
    homer.surname("J. Simpson");                 // free function reacts
    homer.address("742 Evergreen Terrace");      // lambda reacts, count = 1
    marge.address("742 Evergreen Terrace");      // same lambda, count = 2

    std::cout << "\nObserver state survived across subjects: " << moves
              << " address moves seen.\n";

    return 0;
}
