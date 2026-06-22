/*
 * Chapter 12 - Concepts (3/6): Subsumption (overload resolution between constraints)
 *
 * Two overloads of `process`:
 *   - `requires integral<T>`
 *   - `requires (integral<T> && sizeof(T) == 4)` - strictly stronger.
 *
 * For `process(int{1})` both constraints are satisfied. The compiler
 * picks the *more constrained* version - the one with the && of two
 * conditions. This is called *subsumption*: a constraint that implies
 * another wins.
 *
 * For `process(short{2})` only the first constraint is satisfied (short
 * is integral but sizeof(short) != 4 on most platforms), so the simpler
 * overload runs.
 *
 * Output:
 *   integral<T> && sizeof(T) == 4   <- for int{1}
 *   integral<T>                     <- for short{2}
 *
 * Key notes:
 *   - Subsumption replaces the old "more specialized template wins" rule
 *     for constrained overloads.
 *   - Make constraints explicit and composable - they double as
 *     documentation AND drive overload resolution.
 */
#include <concepts>
#include <print>

using namespace std;

template <typename T> requires integral<T>
void process(const T& t) { println("integral<T>"); }

template <typename T> requires (integral<T> && sizeof(T) == 4)
void process(const T& t) { println("integral<T> && sizeof(T) == 4"); }

int main()
{
	process(int{ 1 });
	process(short{ 2 });
}