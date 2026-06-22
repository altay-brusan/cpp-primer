/*
 * Chapter 31 - Assertions
 *
 * Demonstrates the assert() macro from <cassert> to enforce assumptions and fail fast at the
 * exact point a violated invariant is detected, instead of letting bad state propagate. The
 * process() function asserts that the passed vector holds exactly three elements; calling it with
 * two elements trips the assertion and terminates the program. The sample also shows the
 * comma-operator trick for attaching a custom message to an assertion.
 *
 * Key notes:
 *   - assert(("message...", condition)) embeds a human-readable note in the failure output, and
 *     assert(!"text") is the idiom for an assertion that should always fail at a given point.
 *   - assert() is compiled out when NDEBUG is defined (typical for release builds), so never put
 *     side-effecting code inside an assertion; use it only for truly unrecoverable conditions.
 */

#include <vector>
#include <cassert>

using namespace std;

void process(const vector<int>& coordinate)
{
	//assert(coordinate.size() == 3);

	assert(("A custom message...", coordinate.size() == 3));
	
	//assert(!"This should never happen.");
	
	// ...
}

int main()
{
	process({ 1, 2, 3 });
	process({ 1, 2 });
}
