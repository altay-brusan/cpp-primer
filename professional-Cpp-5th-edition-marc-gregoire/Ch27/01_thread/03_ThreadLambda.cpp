/*
 * Chapter 27 - Launching a Thread with a Lambda Expression
 *
 * Lambdas pair naturally with std::thread. Here the lambda captures id and
 * numIterations by value and is handed directly to the thread constructor, which
 * launches it on a new thread. main() then join()s to wait for completion.
 */

#include <print>
#include <thread>

using namespace std;

int main()
{
	int id{ 1 };
	int numIterations{ 5 };
	thread t1{ [id, numIterations] {
		for (int i{ 0 }; i < numIterations; ++i) {
			println("Counter {} has value {}", id, i);
		}
	} };
	t1.join();
}
