/*
 * Chapter 27 - std::barrier: Synchronizing Repeated Phases
 *
 * Unlike a latch, a std::barrier is reusable: a group of threads each call
 * arrive_and_wait() to rendezvous at the end of a phase, and once all have arrived a
 * completion callback runs before the barrier resets for the next phase. This sample runs
 * two "robot" jthreads through several iterations; after each round the completion
 * callback either prepares the next iteration or, on the last one, calls request_stop()
 * on every robot to shut the cooperative jthreads down.
 *
 * Key notes:
 *   - The completion callback runs on exactly one (unspecified) participating thread.
 */

#include <print>
#include <chrono> // newest MSVC no longer pulls <chrono> in transitively via <thread>
#include <format>
#include <thread>
#include <vector>
#include <string_view>
#include <stop_token>
#include <barrier>

using namespace std;

int main()
{
	constexpr unsigned numberOfRobots{ 2 };
	constexpr unsigned numberOfIterations{ 3 };
	unsigned iterationCount{ 1 };

	vector<jthread> robots;

	auto completionCallback{ [&]() noexcept {
		if (iterationCount == numberOfIterations) {
			println("Finished {} iterations, stopping robots.", numberOfIterations);
			for (auto& robot : robots) { robot.request_stop(); }
		} else {
			++iterationCount;
			println("All robots finished. Preparing iteration {}.", iterationCount);
			this_thread::sleep_for(1s);
			println("Iteration {} ready to start. Waking up robots.", iterationCount);
		}
	} };

	barrier robotSynchronization{ numberOfRobots, completionCallback };

	auto robotThreadFunction{ [&](stop_token token, string_view name) {
		println("   Thread for robot {} started.", name);
		while (!token.stop_requested()) {
			this_thread::sleep_for(1s);
			println("   {} finished.", name);
			robotSynchronization.arrive_and_wait();
		}
		println("   {} shutting down.", name);
	} };

	println("Preparing first iteration. Creating {} robot threads.", numberOfRobots);

	for (unsigned i{ 0 }; i < numberOfRobots; ++i) {
		robots.emplace_back(robotThreadFunction, format("Robot_{}", i));
	}

	for (auto& robot : robots) { robot.join(); }
	println("Done with all work.");
}
