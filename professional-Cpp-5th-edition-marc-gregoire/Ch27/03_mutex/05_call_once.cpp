/*
 * Chapter 27 - One-Time Initialization with std::call_once
 *
 * std::call_once together with a std::once_flag guarantees a given function runs exactly
 * once, no matter how many threads reach the call_once call. Here three threads all call
 * processingFunction(), but the shared-resource initialization runs only a single time;
 * the other threads block until that first call completes.
 */

#include <print>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;

once_flag g_onceFlag;

void initializeSharedResources()
{
	// ... Initialize shared resources to be used by multiple threads.

	println("Shared resources initialized.");
}

void processingFunction()
{
	// Make sure the shared resources are initialized.
	call_once(g_onceFlag, initializeSharedResources);

	// ... Do some work, including using the shared resources
	println("Processing");
}

int main()
{
	// Launch 3 threads.
	vector<jthread> threads{ 3 };
	for (auto& t : threads) {
		t = jthread{ processingFunction };
	}

	// No need to manually call join(), as we are using jthread.
}
