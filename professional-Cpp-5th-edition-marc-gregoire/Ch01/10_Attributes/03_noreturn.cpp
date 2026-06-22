/*
 * Chapter 1 - [[noreturn]]
 *
 * [[noreturn]] declares that a function never returns control to the caller - it either
 * terminates the process/thread or throws. With that promise, the compiler can prune
 * spurious diagnostics like "not all control paths return a value" in callers.
 *
 * Key notes:
 *   - The function may still call other functions or throw. "Never returns" means the call
 *     site after it is unreachable.
 *   - Returning from a [[noreturn]] function is undefined behavior.
 *   - Use it on wrappers around std::exit, std::abort, std::terminate, or "throw" helpers.
 *   - The Standard Library also exposes std::unreachable() (C++23) for the same flavor of
 *     contract about unreachable code paths.
 */

#include <print>

using namespace std;

[[noreturn]] void forceProgramTermination()
{
	exit(1);  // Defined in <cstdlib>
}

bool isDongleAvailable()
{
	bool isAvailable{ false };
	// Check whether a licensing dongle is available...
	return isAvailable;
}

bool isFeatureLicensed(int featureId)
{
	if (!isDongleAvailable()) {
		// No licensing dongle found, abort program execution!
		forceProgramTermination();
	} else {
		// Dongle available, perform license check of the given feature...
		bool isLicensed{ featureId == 42 };
		return isLicensed;
	}
}

int main()
{
	bool isLicensed{ isFeatureLicensed(42) };
	println("{}", isLicensed);
}