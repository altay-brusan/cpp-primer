/*
 * Guideline 13 - Design Patterns Are Everywhere (patterns hiding in the STL)
 *
 * The book's claim is that the C++ Standard Library is full of design patterns:
 * almost every abstraction that decouples software is some known pattern, used
 * by intent rather than by a fixed implementation. This single program puts
 * four of those Standard Library patterns side by side so you can see them
 * working in ordinary code. Nothing here is custom infrastructure - every
 * pattern is realized purely with standard components.
 *
 * Key notes (std feature mapped to the pattern it represents):
 *   - Iterator: begin() and end() plus a range-based for walk a container
 *     without exposing how it stores its elements. Traversal is decoupled from
 *     storage, which is exactly the Iterator pattern.
 *   - Strategy: a callable passed to an algorithm customizes one step from the
 *     outside. Here std::accumulate takes the binary operation, and std::sort
 *     takes the comparator. Swapping the callable swaps the behavior.
 *   - Type Erasure: std::function holds any callable that matches one fixed
 *     signature, with no common base class. Different concrete types live behind
 *     a single value type interface.
 *   - Factory: std::make_unique builds an object and hands back an owning handle,
 *     hiding the construction and the raw new from the caller.
 *
 * Standard library only, single translation unit. Builds with MSVC as:
 *   cl /std:c++latest /W4 /EHsc main.cpp
 */
#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <numeric>
#include <string>
#include <vector>

// A tiny product type that the Factory section will create.
struct Widget
{
    std::string name;
    int value{};
};

// Factory pattern: a make function hides construction and returns an owning
// handle. std::make_unique is the Standard Library Factory used underneath.
std::unique_ptr<Widget> makeWidget(std::string name, int value)
{
    return std::make_unique<Widget>(Widget{ std::move(name), value });
}

int main()
{
    // --- Iterator pattern -------------------------------------------------
    // The range-based for uses begin() and end(); we never touch the vector's
    // internal storage. Traversal is decoupled from the container.
    const std::vector<int> nums{ 5, 3, 8, 1, 9, 2 };
    std::cout << "Iterator pattern - walking a container via begin()/end():\n  ";
    for (int n : nums)
    {
        std::cout << n << ' ';
    }
    std::cout << '\n';

    // --- Strategy pattern -------------------------------------------------
    // std::accumulate takes the combining step as a callable. Passing a
    // different strategy (sum vs product) changes the result without touching
    // the algorithm itself.
    const int sum = std::accumulate(nums.begin(), nums.end(), 0,
                                    [](int acc, int x) { return acc + x; });
    const long long product = std::accumulate(nums.begin(), nums.end(), 1LL,
                                    [](long long acc, int x) { return acc * x; });
    std::cout << "Strategy pattern - std::accumulate with a pluggable op:\n"
              << "  sum=" << sum << "  product=" << product << '\n';

    // std::sort is Strategy too: the comparator is the customizable step.
    std::vector<int> sorted{ nums };
    std::sort(sorted.begin(), sorted.end(), std::greater<int>{});
    std::cout << "Strategy pattern - std::sort with std::greater comparator:\n  ";
    for (int n : sorted)
    {
        std::cout << n << ' ';
    }
    std::cout << '\n';

    // --- Type Erasure pattern --------------------------------------------
    // std::function stores any callable matching int(int) behind one value
    // type. A lambda and a free-standing function object coexist in the same
    // vector with no shared base class.
    std::vector<std::function<int(int)>> ops;
    ops.emplace_back([](int x) { return x + 1; });       // a capturing-free lambda
    ops.emplace_back([](int x) { return x * x; });       // a different concrete type
    ops.emplace_back(std::negate<int>{});                // a library function object
    std::cout << "Type Erasure pattern - heterogeneous callables in std::function:\n  ";
    for (const auto& op : ops)
    {
        std::cout << op(4) << ' ';
    }
    std::cout << "(applied to 4)\n";

    // --- Factory pattern --------------------------------------------------
    // makeWidget hides the construction; std::make_unique is the Factory.
    auto w = makeWidget("gizmo", 42);
    std::cout << "Factory pattern - std::make_unique built a Widget:\n"
              << "  name=" << w->name << "  value=" << w->value << '\n';

    return 0;
}
