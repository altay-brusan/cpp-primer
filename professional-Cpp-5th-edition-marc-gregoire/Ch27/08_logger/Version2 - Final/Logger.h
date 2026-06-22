/*
 * Chapter 27 - Background Logger (Version 2, Final): Clean Shutdown
 *
 * The complete producer-consumer logger. Producer threads call log() to enqueue messages
 * under a mutex; a single background thread, woken by a std::condition_variable, drains
 * the queue and writes the entries to a file. This final version adds graceful shutdown:
 * the destructor sets an m_exit flag under the lock, notifies the condition variable, and
 * join()s the background thread, which processes any remaining entries before exiting.
 *
 * Key notes:
 *   - The lock on m_mutex must be released before calling join() in the destructor,
 *     otherwise the background thread can never reacquire it and deadlock results.
 *   - The wait predicate checks m_exit and an empty queue to guard against lost wakeups
 *     and spurious wakeups.
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
	// Gracefully shut down background thread.
	virtual ~Logger();
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
	// Boolean telling the background thread to terminate.
	bool m_exit{ false };
	// Mutex and condition variable to protect access to the queue.
	std::mutex m_mutex;
	std::condition_variable m_condVar;
	std::queue<std::string> m_queue;
	// The background thread.
	std::thread m_thread;
};
