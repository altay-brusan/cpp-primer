/*
 * Chapter 11 - Function-Local statics
 *
 * `static` inside a function gives the variable *static storage duration*
 * (lives for the whole program) but local *scope* (only visible in the
 * function). The classic use is one-time initialization:
 *
 *   - First call: `initialized` is false, the if branch runs, the flag is
 *     set.
 *   - Subsequent calls: `initialized` is true, the branch is skipped.
 *
 * Key notes:
 *   - Initialization of a function-local static is guaranteed to be
 *     thread-safe since C++11 (the "magic statics" rule). The compiler
 *     emits a once-only guard around it.
 *   - This is one of the safer ways to lazily initialize a singleton-like
 *     resource (compared to file-scope globals with order-of-init issues
 *     across translation units - see sample 08).
 */
#include <print>

using namespace std;

void performTask()
{
	static bool initialized{ false };       // initialized only once, on the first call

	if (!initialized) {
		println("initializing");
		// Perform initialization.
		initialized = true;
	}

	// Perform the desired task.
}

int main()
{
	performTask();      // prints "initializing"
	performTask();      // no output - initialization branch skipped
}
