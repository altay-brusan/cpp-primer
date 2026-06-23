/*
 * Guideline 38 - Design Singletons for Change and Testability
 *                (the SOLUTION: invert the dependency with Strategy)
 *
 * The fix is to apply the Strategy design pattern: introduce an abstraction on
 * the HIGH level and let everyone depend on that, not on the concrete database.
 * PersistenceInterface is that abstraction. It splits its operations into a
 * public part (read, write) and a private virtual part (do_read, do_write),
 * following the example of std::pmr::memory_resource - this is the Template
 * Method idea.
 *
 * Alongside the interface we add two global functions, mirroring the book:
 *   - get_persistence_interface() : the global point of ACCESS, and
 *   - set_persistence_interface() : the global point of dependency INJECTION.
 * They read and write the one 'instance' pointer. get_persistence_interface()
 * lazily creates a default Database via an Immediately Invoked Lambda Expression
 * with two static locals, so the default is built only if nobody injected
 * something else first. Database now INHERITS from PersistenceInterface and is a
 * pure implementation detail living on the lowest level.
 *
 * Because Widget and Gadget call get_persistence_interface() and use it through
 * the abstraction, the dependency arrows now point at the high-level interface,
 * not at the concrete database. The Dependency Inversion Principle is satisfied.
 * And testability comes for free: a test injects a CustomPersistence fake with
 * set_persistence_interface() and then verifies what the code under test did -
 * no real database required.
 *
 * Key notes:
 *   - Depend on the abstraction (PersistenceInterface), never on Database. That
 *     single change is what restores the architecture.
 *   - set_persistence_interface() is the injection seam. Call it at the start of
 *     the program, or at the start of a single test, not at arbitrary points.
 *   - The default Database is created lazily and only when needed, so injecting
 *     a fake first avoids building the real database at all.
 *   - The fake records calls, so the test asserts behavior without touching any
 *     real persistence: testability is the direct payoff of inverting.
 *   - Database is immobile (copy and move deleted) but still just an
 *     implementation that can be replaced by any other PersistenceInterface.
 */
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

// ---- The abstraction on the HIGH level (the Strategy interface) ----------
// Public interface plus private virtual implementation (Template Method).
class PersistenceInterface
{
public:
    virtual ~PersistenceInterface() = default;

    bool read(const std::string& key) const { return do_read(key); }
    bool write(const std::string& value) { return do_write(value); }

private:
    virtual bool do_read(const std::string& key) const = 0;
    virtual bool do_write(const std::string& value) = 0;
};

// Global point of access and global point of injection (declared first).
PersistenceInterface* get_persistence_interface();
void set_persistence_interface(PersistenceInterface* persistence);

// The one 'instance' pointer. In the book this is an 'extern' in a header and a
// definition in a .cpp; in this single translation unit it is file scope.
namespace
{
    PersistenceInterface* instance = nullptr;
}

// ---- The default implementation on the LOW level (an implementation detail) -
class Database : public PersistenceInterface
{
public:
    Database() = default;

    // Make the class immobile: there can be only one.
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;
    Database(Database&&) = delete;
    Database& operator=(Database&&) = delete;

private:
    bool do_read(const std::string& key) const override
    {
        std::cout << "[real database] read '" << key << "'\n";
        return true;
    }
    bool do_write(const std::string& value) override
    {
        std::cout << "[real database] write '" << value << "'\n";
        return true;
    }
};

// Lazily provide a default Database, but only if nobody injected an instance
// first. The IILE with two static locals gives us that one-time decision.
PersistenceInterface* get_persistence_interface()
{
    static bool init = []() {
        if (!instance)
        {
            static Database db;
            instance = &db;
        }
        return true; // value is irrelevant; the side effect is the point
    }();
    (void)init;
    return instance;
}

void set_persistence_interface(PersistenceInterface* persistence)
{
    instance = persistence;
}

// ---- Using code depends ONLY on the abstraction --------------------------
class Widget
{
public:
    void doSomething(const std::string& key)
    {
        get_persistence_interface()->read(key);
    }
};

class Gadget
{
public:
    void doSomething(const std::string& value)
    {
        get_persistence_interface()->write(value);
    }
};

// ---- A test double on the LOWEST level (a fake) --------------------------
// It records every call so a test can verify behavior without a real database.
class CustomPersistence : public PersistenceInterface
{
public:
    mutable std::vector<std::string> reads; // mutable: do_read is const
    std::vector<std::string> writes;

private:
    bool do_read(const std::string& key) const override
    {
        reads.push_back(key);
        return true;
    }
    bool do_write(const std::string& value) override
    {
        writes.push_back(value);
        return true;
    }
};

int main()
{
    // Production path: no injection, so the default Database is created lazily
    // on first access through the abstraction.
    std::cout << "Production run (default Database, created on first access):\n";
    Widget w;
    Gadget g;
    w.doSomething("user:42");
    g.doSomething("user:42 logged in");

    // Test path: inject a fake BEFORE the code under test runs. This is the seam
    // the problem sample lacked.
    std::cout << "\nTest run (CustomPersistence injected, no real database):\n";
    CustomPersistence fake;
    set_persistence_interface(&fake);

    Widget testWidget;
    Gadget testGadget;
    testWidget.doSomething("k1");
    testGadget.doSomething("v1");

    // Verify what the code under test actually did - pure, fast, isolated.
    assert(fake.reads.size() == 1 && fake.reads[0] == "k1");
    assert(fake.writes.size() == 1 && fake.writes[0] == "v1");
    std::cout << "fake recorded reads=" << fake.reads.size()
              << " writes=" << fake.writes.size() << " (assertions passed)\n";

    // Restore a safe state before the fake goes out of scope.
    set_persistence_interface(nullptr);

    std::cout << "\nWidget and Gadget never named Database. Depending on the\n"
                 "PersistenceInterface abstraction inverted the dependency and\n"
                 "opened a clean injection seam, so the same code runs against\n"
                 "the real database in production and a fake under test.\n";
    return 0;
}
