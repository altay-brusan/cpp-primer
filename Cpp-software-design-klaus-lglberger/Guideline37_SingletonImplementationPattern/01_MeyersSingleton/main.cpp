/*
 * Guideline 37 - Treat Singleton as an Implementation Pattern, Not a Design Pattern
 *                (the Meyers' Singleton: one instance, global access point)
 *
 * The book's claim, stated up front: Singleton is NOT a design pattern. A design
 * pattern has a name, carries an intent, introduces an ABSTRACTION, and has been
 * proven. Singleton has a name, an intent (ensure a class has exactly one
 * instance and give a global point of access to it), and is proven, but it
 * introduces NO abstraction: no base class, no template parameter, nothing. It
 * does not manage or reduce dependencies, which the book defines as the core of
 * software design. So Singleton is merely an IMPLEMENTATION pattern: it restricts
 * the number of instances to exactly one, an implementation detail.
 *
 * This sample shows the recommended implementation, the Meyers' Singleton: a
 * function-local static inside a static instance() member. The Database below
 * mirrors the book. We prove there is a single shared instance by taking two
 * references and checking their addresses match, and we prove the state is shared
 * by writing through one reference and reading it back through the other.
 *
 * Key notes:
 *   - instance() returns a reference to a function-local static. Since C plus
 *     plus 11 the first thread to reach the declaration initializes it in a
 *     thread-safe way, and every later call simply skips initialization and
 *     returns the same object. No manual locking is needed.
 *   - All other ways to make a Database are blocked: the default constructor is
 *     private, and copy plus move are deleted. instance() is the ONLY door in.
 *   - The default constructor is written out, not defaulted. The book warns that
 *     up to C plus plus 17 a defaulted private constructor would leave the class
 *     an aggregate, so Database db{}; could still create an instance via
 *     aggregate initialization. Writing the constructor removes that loophole.
 *   - No abstraction appears anywhere here: that is exactly why this is an
 *     implementation pattern and not a design pattern.
 *   - Downside to remember: a Singleton is global mutable state. Callers depend
 *     on it implicitly, which hurts testability and changeability. Guideline 38
 *     addresses how to design Singletons for change and testability.
 */
#include <cassert>
#include <iostream>
#include <map>
#include <string>

// Database modeled as a Meyers' Singleton, following the book.
class Database final
{
public:
    // The global access point. The local static is the one, unique instance.
    static Database& instance()
    {
        static Database db; // created once, on first call; thread-safe since C plus plus 11
        return db;
    }

    // Ordinary database-like functionality acting on shared state.
    void write(const std::string& key, const std::string& value)
    {
        m_store[key] = value;
    }

    std::string read(const std::string& key) const
    {
        const auto it = m_store.find(key);
        return it != m_store.end() ? it->second : std::string{"<missing>"};
    }

    std::size_t size() const { return m_store.size(); }

private:
    // Written out, NOT defaulted, so the class is not an aggregate (see header).
    Database() {}

    // Every copy or move path is closed: instance() is the only way to obtain one.
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;
    Database(Database&&) = delete;
    Database& operator=(Database&&) = delete;

    std::map<std::string, std::string> m_store; // the single shared state
};

int main()
{
    // First access creates the object; second access returns the SAME object.
    Database& db1 = Database::instance();
    Database& db2 = Database::instance();

    assert(&db1 == &db2); // same address: there is exactly one instance
    std::cout << "db1 and db2 refer to the same instance: "
              << ((&db1 == &db2) ? "yes" : "no") << '\n';

    // Write through one reference.
    db1.write("user", "alice");
    db1.write("role", "admin");

    // Read back through the other reference: the state is shared.
    std::cout << "via db2, user = " << db2.read("user") << '\n';
    std::cout << "via db2, role = " << db2.read("role") << '\n';
    std::cout << "entry count seen by db1 = " << db1.size() << '\n';

    // A third, independent access still lands on the very same global state.
    std::cout << "via instance(), user = " << Database::instance().read("user") << '\n';

    std::cout << "\nOne instance, global access, shared mutable state: that is all\n"
                 "Singleton does. It introduces no abstraction and decouples\n"
                 "nothing, so it is an implementation pattern, not a design pattern.\n";
    return 0;
}
