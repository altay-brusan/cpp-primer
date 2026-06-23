/*
 * Guideline 25 - Apply Observers as an Abstract Notification Mechanism
 *                (the classic, template based Observer design pattern)
 *
 * Concern: in many situations we want feedback the moment some state changes
 * (a name is edited, an address is updated, a result is ready). But we do NOT
 * want the observed entity (the SUBJECT) to depend on the concrete reactions.
 * Any direct dependency from subject to its many reactions would make the code
 * harder to change and harder to extend. The Observer pattern extracts the
 * "need to add new reactions" as the variation point and turns it into an
 * abstraction: the Observer base class. The subject is then oblivious to the
 * potentially many kinds of observers (a one to many relationship).
 *
 * Grounding in the book:
 *   - The Observer base class is the abstraction (SRP extracts the variation
 *     point; that SRP then enables the OCP, so new observers are added without
 *     touching existing code).
 *   - Observer is a CLASS TEMPLATE over Subject and StateTag, lifting it to the
 *     highest architectural level so it can be reused by many subjects.
 *   - This sample uses the book's preferred PULL plus TAG update: update()
 *     receives the subject by const reference plus a tag saying WHICH property
 *     changed. The observer pulls only the data it cares about and uses the tag
 *     to decide whether the change is interesting at all.
 *   - Observers are held as RAW POINTERS in a std::set. The pointer is just a
 *     unique handle, NOT ownership (Core Guideline F.7); an owning smart pointer
 *     would be the wrong tool here, so observer lifetime stays with the caller.
 *
 * Key notes:
 *   - attach() and detach() register and deregister by address; a std::set
 *     rejects a duplicate registration (returns false), the book's choice.
 *   - notify() walks the set so that an observer detaching itself during the
 *     callback does not invalidate the loop (it advances the iterator first).
 *   - Each setter passes a different tag, so observers can filter precisely and
 *     never have to "search" for what changed.
 *   - PUSH vs PULL: push would hand the changed values straight to update();
 *     pull (used here) hands only the subject plus a tag, trading a small
 *     coupling to the subject for independence from the argument list.
 */
#include <iostream>
#include <set>
#include <string>
#include <utility>

// The abstraction: one Observer interface per (Subject, StateTag) pairing.
// As a template it depends on no concrete subject, so it can live at the top
// of the architecture and be reused by many different subjects.
template <typename Subject, typename StateTag>
class Observer
{
public:
    virtual ~Observer() = default;
    // Pull plus tag: receive the subject and a tag for the changed property.
    virtual void update(const Subject& subject, StateTag property) = 0;
};

// The concrete subject. A Person is merely an aggregate of three fields plus a
// set of registered observers. It knows nothing about what the observers do.
class Person
{
public:
    enum StateChange
    {
        forenameChanged,
        surnameChanged,
        addressChanged
    };

    // The subject instantiates its OWN observer type from the template.
    using PersonObserver = Observer<Person, StateChange>;

    Person(std::string forename, std::string surname)
        : m_forename(std::move(forename)), m_surname(std::move(surname))
    {
    }

    // Register by address; the set rejects a second registration.
    bool attach(PersonObserver* observer)
    {
        auto [pos, success] = m_observers.insert(observer);
        (void)pos;
        return success;
    }

    // Deregister; true only if the observer was actually present.
    bool detach(PersonObserver* observer)
    {
        return m_observers.erase(observer) > 0U;
    }

    // Setters change one field and notify with the matching tag.
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
    // Notify every registered observer. The iterator is advanced BEFORE the
    // callback so an observer may safely detach itself during update().
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
    std::set<PersonObserver*> m_observers; // raw handles, NOT owners
};

// A concrete observer reacting only to NAME changes. It pulls the data it wants
// from the subject and uses the tag to ignore everything else.
class NameObserver : public Observer<Person, Person::StateChange>
{
public:
    void update(const Person& person, Person::StateChange property) override
    {
        if (property == Person::forenameChanged || property == Person::surnameChanged)
        {
            std::cout << "[name ] now: " << person.forename() << ' '
                      << person.surname() << '\n';
        }
    }
};

// A second concrete observer reacting only to ADDRESS changes. Adding it
// required no change to Person or to NameObserver: open for extension.
class AddressObserver : public Observer<Person, Person::StateChange>
{
public:
    void update(const Person& person, Person::StateChange property) override
    {
        if (property == Person::addressChanged)
        {
            std::cout << "[addr ] " << person.forename() << " moved to: "
                      << person.address() << '\n';
        }
    }
};

int main()
{
    NameObserver nameObserver;
    AddressObserver addressObserver;

    Person homer("Homer", "Simpson");
    Person marge("Marge", "Simpson");

    // Attach observers (the subject stays oblivious to their concrete types).
    homer.attach(&nameObserver);
    homer.attach(&addressObserver);
    marge.attach(&addressObserver);

    std::cout << "Triggering state changes (subject notifies observers):\n";
    homer.forename("Homer Jay");                 // name observer reacts
    homer.address("742 Evergreen Terrace");      // address observer reacts
    marge.address("742 Evergreen Terrace");      // same observer, other subject

    // A second attach of the same observer is rejected by the std::set.
    std::cout << "\nattach again -> " << (homer.attach(&nameObserver) ? "ok" : "rejected")
              << '\n';

    // Detach and show the silenced channel: no name notification now.
    homer.detach(&nameObserver);
    std::cout << "after detaching the name observer, a name change is silent:\n";
    homer.forename("Homer J.");

    return 0;
}
