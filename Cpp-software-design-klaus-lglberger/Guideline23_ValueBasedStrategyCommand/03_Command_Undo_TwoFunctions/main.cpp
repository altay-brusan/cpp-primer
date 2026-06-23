/*
 * Guideline 23 - Value-Based Command with undo, and its honest shortcoming
 *                (one std::function per virtual function)
 *
 * The book is candid about the limits of the value-based approach: a single
 * std::function can replace only a SINGLE virtual function. The Command pattern
 * often needs more than one operation, the classic example being an undo(). When
 * a command must both execute() and undo(), one std::function is not enough; you
 * reach for TWO std::function members, one per operation.
 *
 * This sample makes that trade-off concrete with a calculator whose value is
 * changed by commands. Each command bundles a do-action and an undo-action. The
 * command stack lets us replay and then roll back. Two callables per command is
 * the cost; it still avoids a Command base class, but the book notes that as the
 * number of operations grows, the multiple-std::function interface becomes
 * awkward, and full Type Erasure (Chapter 8) is then the better generalization.
 *
 * Key notes:
 *   - std::function abstracts ONE callable; undo() is a second operation, so the
 *     command needs a second std::function member.
 *   - Each member is built from a lambda capturing the operand, so there is
 *     still no per-command class and no Command base class.
 *   - An undo stack stores commands by value and rolls them back in reverse.
 *   - This is the documented downside: for several virtual functions the
 *     per-function std::function count grows, and Type Erasure generalizes the
 *     idea more cleanly.
 */
#include <functional>
#include <iostream>
#include <utility>
#include <vector>

// One std::function per operation: a do-action and its inverse undo-action.
class CalculatorCommand
{
public:
    using Operation = std::function<int(int)>;

    CalculatorCommand(Operation execute, Operation undo)
        : m_execute(std::move(execute)), m_undo(std::move(undo))
    {
    }

    int execute(int value) const { return m_execute(value); }
    int undo(int value) const { return m_undo(value); }

private:
    Operation m_execute;
    Operation m_undo;
};

// Factory helpers keep the call sites short and readable.
CalculatorCommand add(int operand)
{
    return CalculatorCommand{
        [operand](int v) { return v + operand; },
        [operand](int v) { return v - operand; }};
}

CalculatorCommand subtract(int operand)
{
    return CalculatorCommand{
        [operand](int v) { return v - operand; },
        [operand](int v) { return v + operand; }};
}

int main()
{
    int value = 0;
    std::vector<CalculatorCommand> history;

    auto apply = [&](const CalculatorCommand& cmd) {
        value = cmd.execute(value);
        history.push_back(cmd);
        std::cout << "  execute -> " << value << '\n';
    };

    std::cout << "Applying commands (each carries do and undo callables):\n";
    apply(add(10));
    apply(subtract(3));
    apply(add(5));

    std::cout << "Value after all commands: " << value << '\n';

    std::cout << "\nUndoing in reverse order:\n";
    while (!history.empty())
    {
        value = history.back().undo(value);
        history.pop_back();
        std::cout << "  undo    -> " << value << '\n';
    }

    std::cout << "Value after full undo: " << value << '\n';

    std::cout << "\nTwo operations meant two std::function members per command:\n"
                 "the honest cost of the value-based approach. For many virtual\n"
                 "functions, Type Erasure generalizes this more cleanly.\n";
    return 0;
}
