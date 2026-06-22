/*
 * Chapter 27 - Background Logger (Version 1): Driver
 *
 * Exercises the Logger class: it creates one shared Logger and launches ten threads that
 * each log a series of messages to it concurrently, demonstrating the thread-safe queue
 * and background-writer design. Must be compiled and linked together with Logger.cpp
 * (this file has main(); Logger.cpp does not). Writes output to log.txt.
 */

#include "Logger.h"
#include <chrono> // newest MSVC no longer pulls <chrono> in transitively via <thread>
#include <format>
#include <thread>
#include <vector>
#include <utility>

using namespace std;

void logSomeMessages(int id, Logger& logger)
{
	for (int i{ 0 }; i < 10; ++i) {
		logger.log(format("Log entry {} from thread {}", i, id));
		this_thread::sleep_for(50ms);
	}
}

int main()
{
	Logger logger;

	vector<jthread> threads;
	// Create a few threads all working with the same Logger instance.
	for (int i{ 0 }; i < 10; ++i) {
		threads.emplace_back(logSomeMessages, i, ref(logger));
	}
}
