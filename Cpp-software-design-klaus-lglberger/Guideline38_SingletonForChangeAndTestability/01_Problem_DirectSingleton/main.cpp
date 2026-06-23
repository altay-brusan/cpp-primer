/*
 * Guideline 38 - Design Singletons for Change and Testability
 *                (the PROBLEM: depending on a concrete Singleton directly)
 *
 * The book revives the Database Singleton and lets ordinary classes - here
 * Widget and Gadget - use it directly through Database::instance(). Database is
 * NOT an abstraction; it is a concrete implementation that stands for one very
 * specific database. Every call to Database::instance().read() or .write()
 * therefore hard-wires a dependency on that concrete implementation deep inside
 * the using code.
 *
 * This wrecks the architecture. We would like Widget and Gadget to sit BELOW the
 * Database so the dependency arrows point toward the high level. But because
 * Database is concrete, the arrows actually point at the low-level detail: the
 * Dependency Inversion Principle is violated and there is, in effect, no
 * architecture. The dependency is also invisible - nothing in doSomething's
 * signature reveals that it reaches out to global state.
 *
 * Worst of all is testability. There is no seam: the functions give you no way
 * to substitute the Database with a stub, mock, or fake. Any test of
 * Widget::doSomething must therefore drag in the one real Database, which is
 * exactly what kills testability and tempts people not to write tests at all.
 *
 * Key notes:
 *   - Database::instance() returns a concrete type, so callers depend on the
 *     implementation, not on an abstraction. That is the core defect.
 *   - The coupling is global and hidden: the dependency lives in the body, not
 *     in the interface, so it is easy to miss and hard to reason about.
 *   - No substitution point exists. To test Widget you must use the real
 *     Database; there is no place to inject a test double.
 *   - This sample compiles and runs, but the "real database" message printed at
 *     construction stands in for the slow, side-effecting dependency a test
 *     would be forced to touch.
 *   - Fix in sample 02: invert the dependency with a PersistenceInterface
 *     abstraction so callers depend on the interface, not on Database.
 */
#include <iostream>
#include <string>

// The concrete Database Singleton (a Meyers' Singleton). It represents ONE
// specific database - a concrete implementation detail, not an abstraction.
class Database
{
public:
    static Database& instance()
    {
        static Database db; // created on first access
        return db;
    }

    // A real implementation would open sockets, run queries, touch disk...
    bool read(const std::string& key)
    {
        std::cout << "[real database] read '" << key << "'\n";
        return true;
    }
    bool write(const std::string& value)
    {
        std::cout << "[real database] write '" << value << "'\n";
        return true;
    }

    // Immobile: there can be only one.
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

private:
    Database()
    {
        std::cout << "[real database] connecting to the production server...\n";
    }
};

// Widget depends DIRECTLY on the concrete Database. The dependency is hidden in
// the body; the signature does not admit to it.
class Widget
{
public:
    void doSomething(const std::string& key)
    {
        Database::instance().read(key); // hard-wired to the concrete Singleton
    }
};

// Gadget does the same on the write side.
class Gadget
{
public:
    void doSomething(const std::string& value)
    {
        Database::instance().write(value); // hard-wired to the concrete Singleton
    }
};

int main()
{
    std::cout << "Using Widget and Gadget, both wired to the real Database:\n";
    Widget w;
    Gadget g;
    w.doSomething("user:42");
    g.doSomething("user:42 logged in");

    std::cout << "\nThere is no seam here: a test of Widget::doSomething cannot\n"
                 "swap the Database for a fake, because the call names the\n"
                 "concrete Singleton directly. The dependency is inverted the\n"
                 "WRONG way - toward the low-level detail. Sample 02 fixes this.\n";
    return 0;
}
