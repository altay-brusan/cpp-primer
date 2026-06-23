/*
 * Guideline 21 - Use Command to Isolate What Things Are Done
 *                (Command without undo: a scheduled task queue)
 *
 * The book's second classic example is a thread pool that schedules work
 * packages. Here it is shrunk to a deterministic, single threaded TaskQueue so
 * the output is stable and the code stays standard library only, but the design
 * lesson is identical. The queue is the Invoker; it accepts any Command through
 * the abstraction and later runs each one, completely decoupled from WHAT the
 * task actually does.
 *
 * This sample also makes the book's point that undo() is an OPTIONAL feature of
 * Command, not a defining one. A FormatCommand or a PrintCommand has nothing to
 * roll back, yet it is still a Command, because the intent is to specify WHAT
 * should be done. The same reasoning is why std::for_each takes a Command.
 *
 * Key notes:
 *   - The TaskQueue depends only on the Command abstraction. It can schedule,
 *     store, and later run any task without knowing the concrete kind.
 *   - Commands are queued now and executed later, the parameterize and queue
 *     requests aspect of the Gang of Four intent.
 *   - There is no undo() here, and that is fine: the book treats undo as optional
 *     and reminds us its absence is not proof of Strategy.
 *   - Adding a new task (here PrintCommand alongside FormatCommand) needs no
 *     change to the queue: open for extension, closed for modification.
 */
#include <iostream>
#include <memory>
#include <queue>
#include <string>
#include <utility>

// The abstraction: a unit of work to be performed. No undo is needed.
class Command
{
public:
    virtual ~Command() = default;
    virtual void execute() const = 0;
};

// One kind of work package: pretend to format a disk.
class FormatCommand : public Command
{
public:
    explicit FormatCommand(std::string disk) : disk_(std::move(disk)) {}
    void execute() const override
    {
        std::cout << "[format] preparing disk " << disk_ << '\n';
    }

private:
    std::string disk_;
};

// Another kind of work package: pretend to run a print job.
class PrintCommand : public Command
{
public:
    explicit PrintCommand(std::string doc) : doc_(std::move(doc)) {}
    void execute() const override
    {
        std::cout << "[print] sending document " << doc_ << " to the printer\n";
    }

private:
    std::string doc_;
};

// The Invoker: it knows nothing about the concrete tasks it runs.
class TaskQueue
{
public:
    void schedule(std::unique_ptr<Command> command)
    {
        tasks_.push(std::move(command));
    }

    // Drain the queue, running each scheduled work package in order.
    void run()
    {
        while (!tasks_.empty())
        {
            auto task = std::move(tasks_.front());
            tasks_.pop();
            task->execute();
        }
    }

    bool empty() const { return tasks_.empty(); }
    std::size_t size() const { return tasks_.size(); }

private:
    std::queue<std::unique_ptr<Command>> tasks_;
};

int main()
{
    TaskQueue queue{};

    // Tasks are captured as objects now, run later, varied independently.
    queue.schedule(std::make_unique<FormatCommand>("D:"));
    queue.schedule(std::make_unique<PrintCommand>("report.pdf"));
    queue.schedule(std::make_unique<FormatCommand>("E:"));

    std::cout << "scheduled " << queue.size() << " tasks, running them now:\n";
    queue.run();

    std::cout << "\nThe queue stored and ran every task through the Command\n"
                 "abstraction without knowing what each one does. No undo is\n"
                 "needed here: undo is an optional feature of Command, not a\n"
                 "defining one. Command isolates WHAT is done.\n";
    return 0;
}
