/*
 * Guideline 24 - Adapters in the Standard Library
 *                (standardize a container behind a stack interface)
 *
 * The book points out that the Standard Library uses the Adapter pattern to
 * standardize the interface of different containers. Two flavors are shown here.
 *
 * First, the runtime version from the book: an abstract Stack<T> base that
 * declares the expected stack operations (top, empty, size, push, pop), and a
 * VectorStack<T> adapter that implements them over a std::vector. Any data
 * structure can be adapted to the Stack interface this way, nonintrusively.
 *
 * Second, the form the library actually uses for efficiency: the container
 * ADAPTOR class templates std::stack, std::queue, std::priority_queue. They
 * adapt a given container (here std::vector) to a special-purpose interface at
 * compile time, with no virtual calls. Same intent as the abstract Stack, but
 * via static polymorphism. Both serve as a variation point: new adapters plug
 * in without modifying existing code.
 *
 * Key notes:
 *   - std::stack and friends are Adapters: they wrap a container and re-present
 *     it through a narrowed, purpose-built interface (top, push, pop, ...).
 *   - The abstract Stack base is the runtime twin; the class template is the
 *     compile-time twin chosen by the library to avoid virtual-call overhead.
 *   - Adapter vs Strategy: the Container parameter supplies most or all of the
 *     behavior and is fixed once; Strategy injects one aspect, meant to be
 *     reconfigured. Similar structure, different intent.
 *   - Function adapters (free begin and end) adapt via overloading; the same
 *     standardizing idea expressed through compile-time function lookup.
 */
#include <cstddef>
#include <iostream>
#include <memory>
#include <stack>
#include <vector>

// The expected stack interface (runtime polymorphism), from the book.
template <typename T>
class Stack
{
public:
    virtual ~Stack() = default;
    virtual T& top() = 0;
    virtual bool empty() const = 0;
    virtual std::size_t size() const = 0;
    virtual void push(const T& value) = 0;
    virtual void pop() = 0;
};

// An adapter that standardizes a std::vector behind the Stack interface.
template <typename T>
class VectorStack : public Stack<T>
{
public:
    T& top() override { return vec_.back(); }
    bool empty() const override { return vec_.empty(); }
    std::size_t size() const override { return vec_.size(); }
    void push(const T& value) override { vec_.push_back(value); }
    void pop() override { vec_.pop_back(); }

private:
    std::vector<T> vec_;
};

// A client that depends only on the abstract Stack interface.
void drain(Stack<int>& s)
{
    std::cout << "  size " << s.size() << ": ";
    while (!s.empty())
    {
        std::cout << s.top() << ' ';
        s.pop();
    }
    std::cout << '\n';
}

int main()
{
    std::cout << "Runtime adapter (VectorStack over the Stack interface):\n";
    std::unique_ptr<Stack<int>> s = std::make_unique<VectorStack<int>>();
    s->push(1);
    s->push(2);
    s->push(3);
    drain(*s);

    std::cout << "\nLibrary container adaptor (std::stack over a std::vector):\n";
    std::stack<int, std::vector<int>> lib;
    lib.push(10);
    lib.push(20);
    lib.push(30);
    std::cout << "  size " << lib.size() << ": ";
    while (!lib.empty())
    {
        std::cout << lib.top() << ' ';
        lib.pop();
    }
    std::cout << '\n';

    std::cout << "\nBoth adapt a container to a stack interface: one at runtime,\n"
                 "one at compile time. That is the Adapter pattern standardizing\n"
                 "interfaces.\n";
    return 0;
}
