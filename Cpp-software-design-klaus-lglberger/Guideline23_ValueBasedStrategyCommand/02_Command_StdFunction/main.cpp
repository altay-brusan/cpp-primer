/*
 * Guideline 23 - Prefer a Value-Based Implementation of Command
 *                (Command via std::function, no Command base class)
 *
 * The Command design pattern (Guideline 21) isolates WHAT is done by wrapping an
 * action in an object so it can be stored, queued, passed around, and run later.
 * The classic form uses a Command base class with a virtual execute(). But a
 * command that only needs execute() is, in essence, a single callable, and a
 * single callable is exactly what std::function abstracts by value.
 *
 * So a command queue becomes a std::vector<std::function<void()>>. Each entry
 * can be a lambda (often capturing its own arguments), a free function, or a
 * functor. There is no Command base class, no derived command per action, and no
 * heap-allocated, pointer-owned command objects to manage.
 *
 * Key notes:
 *   - A command is std::function<void()>: a value-semantics, type-erased action.
 *   - Lambdas capture the parameters a command needs, replacing per-command
 *     classes with their own data members and constructors.
 *   - Commands are stored and replayed from a plain container; copying the queue
 *     copies the commands (deep copy of each contained callable).
 *   - This matches Strategy via std::function (sample 01): both patterns reduce
 *     to abstracting a single callable, so the same value-based tool fits both.
 */
#include <functional>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

// A command is simply a callable that performs an action and returns nothing.
using Command = std::function<void()>;

// A tiny in-memory account the commands will act upon.
class Account
{
public:
    void deposit(int amount)
    {
        m_balance += amount;
        std::cout << "  deposit " << amount << " -> balance " << m_balance << '\n';
    }

    void withdraw(int amount)
    {
        m_balance -= amount;
        std::cout << "  withdraw " << amount << " -> balance " << m_balance << '\n';
    }

    int balance() const { return m_balance; }

private:
    int m_balance{0};
};

// A free function can also serve as a command (it matches void()).
void greet()
{
    std::cout << "  [free fn] processing batch\n";
}

int main()
{
    Account account;

    // Build a queue of commands. Each lambda captures the data it needs, so no
    // per-action Command subclass is required.
    std::vector<Command> queue;
    queue.emplace_back([&account] { account.deposit(100); });
    queue.emplace_back([&account] { account.withdraw(30); });
    queue.emplace_back(greet);
    queue.emplace_back([&account] { account.deposit(5); });

    std::cout << "Replaying a queue of std::function commands (no base class):\n";
    for (const Command& cmd : queue)
        cmd();

    std::cout << "Final balance: " << account.balance() << '\n';

    // Commands are values: a command can be stored and invoked on its own, and
    // copying it copies the contained callable.
    Command single = [] { std::cout << "  stored command executed later\n"; };
    Command copy = single;
    std::cout << "\nA command is a value (stored, copied, invoked on demand):\n";
    copy();

    std::cout << "\nWHAT to do is wrapped in std::function and replayed from a\n"
                 "plain container. No Command hierarchy, no owning pointers.\n";
    return 0;
}
