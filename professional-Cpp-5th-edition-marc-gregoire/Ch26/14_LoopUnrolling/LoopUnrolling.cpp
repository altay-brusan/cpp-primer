/*
 * Chapter 26 - Template Metaprogramming: Loop Unrolling
 *
 * Uses template recursion to unroll a loop at compile time. Loop<i>::run()
 * recursively instantiates Loop<i-1>::run() and then invokes the supplied
 * functor with i; the full specialization Loop<0> stops the recursion. The
 * result is the body emitted inline for each iteration rather than an actual
 * run-time loop.
 *
 * Key notes:
 *   - Manual loop unrolling is rarely needed; compilers usually unroll loops on
 *     their own when beneficial.
 */

#include <print>

using namespace std;

template <int i>
class Loop
{
public:
	template <typename FuncType>
	static void run(FuncType func) {
		Loop<i - 1>::run(func);
		func(i);
	}
};

template <>
class Loop<0>
{
public:
	template <typename FuncType>
	static void run(FuncType /* func */) { }
};

void doWork(int i)
{
	println("doWork({})", i);
}

int main()
{
	Loop<3>::run(doWork);
}
