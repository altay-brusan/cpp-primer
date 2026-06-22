/*
 * Chapter 27 - Background Logger (Version 1): Condition Variable Producer-Consumer
 *
 * A worked example combining many threading building blocks. Producer threads call log()
 * to push messages onto a shared queue protected by a mutex, and a single background
 * thread consumes them and writes them to a file. A std::condition_variable lets the
 * background thread sleep until log() notifies it that new work has arrived, instead of
 * busy-waiting. Copy construction and assignment are deleted because the class owns a
 * running thread.
 *
 * Key notes:
 *   - This is Version 1: it has no clean shutdown, so the background thread loops forever
 *     and the still-joinable std::thread is destroyed without join(), calling
 *     std::terminate(). Version 2 fixes this.
 *   - The queue is swapped into a local queue under the lock, then processed after
 *     unlocking, so producers are not blocked during the (slow) file I/O.
 */

#pragma once

#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <fstream>

class Logger
{
public:
	// Starts a background thread writing log entries to a file.
	Logger();
	// Prevent copy construction and assignment.
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;
	// Add log entry to the queue.
	void log(std::string entry);

private:
	// The function running in the background thread.
	void processEntries();
	// Helper member function to process a queue of entries.
	void processEntriesHelper(std::queue<std::string>& queue, std::ofstream& ofs) const;
	// Mutex and condition variable to protect access to the queue.
	std::mutex m_mutex;
	std::condition_variable m_condVar;
	std::queue<std::string> m_queue;
	// The background thread.
	std::thread m_thread;
};
