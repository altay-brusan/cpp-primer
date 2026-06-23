/*
 * Guideline 21 - Use Command to Isolate What Things Are Done
 *                (the problem: a calculator that cannot undo and cannot grow)
 *
 * A first calculator hardcodes every operation inside one apply() member that
 * switches on an enum. It computes immediately, which is fine, but the WHAT
 * (which action was performed) is never captured as an object. Two pains follow,
 * both predicted by the book:
 *   - There is no record of the action, so the calculator cannot roll anything
 *     back. The book stresses that an action which owns everything needed to
 *     reverse itself is the hallmark of Command; here no such action exists.
 *   - Adding a new operation means editing the enum AND the switch, so the class
 *     is modified for every extension. That violates the Open Closed Principle,
 *     the very principle Command is meant to serve.
 *
 * This file is the BEFORE picture: it compiles and runs, but the action is not a
 * first class thing, so it cannot be passed, queued, stored, or undone.
 *
 * Key notes:
 *   - The action is implicit (an enum tag plus a switch), not an object. It
 *     cannot be handed to a queue or kept on a stack for later reversal.
 *   - undo() is impossible: the calculator keeps only the current value, not the
 *     work packages that produced it.
 *   - Every new operation forces a change to existing code (enum plus switch),
 *     so the design is closed against the change the book says is coming.
 *   - Contrast with the next sample, where each action becomes a Command object
 *     that knows how to execute AND reverse itself.
 */
#include <iostream>

class Calculator
{
public:
    enum class Op
    {
        Add,
        Subtract
    };

    // Immediate execution, but the action vanishes the moment it runs.
    void apply(Op op, int operand)
    {
        switch (op)
        {
        case Op::Add:
            current_ += operand;
            break;
        case Op::Subtract:
            current_ -= operand;
            break;
            // A new operation (say Multiply) forces a new case here AND a new
            // enum value above: existing code must be modified to extend.
        }
    }

    int result() const { return current_; }

private:
    int current_{};
};

int main()
{
    Calculator calc{};

    calc.apply(Calculator::Op::Add, 3);      // 0 plus 3  is 3
    calc.apply(Calculator::Op::Add, 7);      // 3 plus 7  is 10
    calc.apply(Calculator::Op::Subtract, 4); // 10 minus 4 is 6
    calc.apply(Calculator::Op::Subtract, 2); // 6 minus 2 is 4

    std::cout << "result after four operations: " << calc.result() << '\n';

    std::cout << "\nProblem: the actions were never captured as objects, so the\n"
                 "calculator cannot undo the last step, and adding a new operation\n"
                 "means editing the enum and the switch. The WHAT is not isolated.\n";
    return 0;
}
