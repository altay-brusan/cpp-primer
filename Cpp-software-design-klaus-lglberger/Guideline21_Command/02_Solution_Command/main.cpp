/*
 * Guideline 21 - Use Command to Isolate What Things Are Done
 *                (the Command design pattern: encapsulate WHAT is done)
 *
 * The book's calculator, redesigned. Each action becomes an object derived from
 * a CalculatorCommand abstraction that knows how to execute() itself and how to
 * undo() that effect. The intent of Command, per the Gang of Four and quoted in
 * the book, is to encapsulate a request as an object so clients can be
 * parameterized with different requests, requests can be queued or logged, and
 * undoable operations are supported.
 *
 * The Calculator becomes the Invoker: it keeps a current value and a stack of the
 * commands it has executed. compute() runs a command immediately and stores it;
 * undoLast() pops the most recent command and calls its undo(). Because the
 * variation point (which action) is extracted into the hierarchy, compute() and
 * undoLast() need not be virtual, and new operations are added by writing a new
 * command class, touching no existing code.
 *
 * Key notes:
 *   - The action is now a first class object: it can be passed, stored on a
 *     stack, and reversed later. That is exactly what the enum plus switch in the
 *     problem sample could not do.
 *   - undo() lives inside each command, which owns everything needed to reverse
 *     its own effect (Add reverses with a subtraction, Subtract with an addition).
 *     The book calls a self contained undo the hallmark of Command.
 *   - The action is performed immediately, not injected to configure an object.
 *     The book names this the key tell of Command versus Strategy.
 *   - Adding Multiply below touched no existing class: open for extension, closed
 *     for modification (the Single Responsibility Principle enabling the Open
 *     Closed Principle).
 *   - Ownership flows through unique_ptr to the high level Calculator, so the
 *     design also respects the Dependency Inversion Principle.
 */
#include <iostream>
#include <memory>
#include <stack>
#include <utility>

// The abstraction: any action on an integer that can be done and undone.
class CalculatorCommand
{
public:
    virtual ~CalculatorCommand() = default;
    virtual int execute(int i) const = 0;
    virtual int undo(int i) const = 0;
};

// Add knows how to apply itself and how to reverse itself.
class Add : public CalculatorCommand
{
public:
    explicit Add(int operand) : operand_(operand) {}
    int execute(int i) const override { return i + operand_; }
    int undo(int i) const override { return i - operand_; }

private:
    int operand_{};
};

// Subtract is the inverse of Add.
class Subtract : public CalculatorCommand
{
public:
    explicit Subtract(int operand) : operand_(operand) {}
    int execute(int i) const override { return i - operand_; }
    int undo(int i) const override { return i + operand_; }

private:
    int operand_{};
};

// A brand new operation added WITHOUT editing any existing class.
class Multiply : public CalculatorCommand
{
public:
    explicit Multiply(int operand) : operand_(operand) {}
    int execute(int i) const override { return i * operand_; }
    // Reversing a multiply by a nonzero operand is an integer division.
    int undo(int i) const override { return operand_ != 0 ? i / operand_ : i; }

private:
    int operand_{};
};

// The Invoker: runs commands now, keeps them for later reversal.
class Calculator
{
public:
    void compute(std::unique_ptr<CalculatorCommand> command)
    {
        current_ = command->execute(current_);
        stack_.push(std::move(command));
    }

    void undoLast()
    {
        if (stack_.empty())
            return;
        auto command = std::move(stack_.top());
        stack_.pop();
        current_ = command->undo(current_);
    }

    int result() const { return current_; }

    void clear()
    {
        current_ = 0;
        CommandStack{}.swap(stack_);
    }

private:
    using CommandStack = std::stack<std::unique_ptr<CalculatorCommand>>;
    int current_{};
    CommandStack stack_;
};

int main()
{
    Calculator calc{};

    calc.compute(std::make_unique<Add>(3));      // 0 plus 3  is 3
    calc.compute(std::make_unique<Add>(7));      // 3 plus 7  is 10
    calc.compute(std::make_unique<Subtract>(4)); // 10 minus 4 is 6
    calc.compute(std::make_unique<Subtract>(2)); // 6 minus 2 is 4
    std::cout << "after Add 3, Add 7, Subtract 4, Subtract 2: " << calc.result() << '\n';

    calc.undoLast(); // reverts the last Subtract 2, back to 6
    std::cout << "after one undo: " << calc.result() << '\n';

    calc.undoLast(); // reverts the Subtract 4, back to 10
    std::cout << "after a second undo: " << calc.result() << '\n';

    // The freshly added Multiply command plugs straight in.
    calc.compute(std::make_unique<Multiply>(5)); // 10 times 5 is 50
    std::cout << "after Multiply 5: " << calc.result() << '\n';
    calc.undoLast(); // reverses the multiply, back to 10
    std::cout << "after undoing the multiply: " << calc.result() << '\n';

    std::cout << "\nEach action is an object that can execute and undo itself, so\n"
                 "the calculator can store actions on a stack and roll them back.\n"
                 "Multiply was added without touching any existing class. Command\n"
                 "isolates WHAT is done.\n";
    return 0;
}
