/*
 * Chapter 33 - Singleton Pattern in Action
 *
 * Driver for the Singleton Logger. It sets the log filename, then repeatedly
 * reaches the same shared logger through Logger::instance() to change the log
 * level and write messages. Because every call returns the one instance, state
 * such as the current log level persists across calls - a message logged below
 * the active level is silently dropped.
 *
 * Key notes:
 *   - setLogFilename() must be called before the first instance() call.
 *   - Contains main(); run as a standalone program (writes to log.out).
 */

#include "Logger.h"

using namespace std;

int main()
{
	// Set the log filename before the first call to instance().
	Logger::setLogFilename("log.out");

	// Set log level to Debug.
	Logger::instance().setLogLevel(Logger::LogLevel::Debug);

	// Log some messages.
	Logger::instance().log("test message", Logger::LogLevel::Debug);

	// Set log level to Error.
	Logger::instance().setLogLevel(Logger::LogLevel::Error);

	// Now that the log level is set to Error, logging a Debug
	// message will be ignored.
	Logger::instance().log("A debug message", Logger::LogLevel::Debug);
}
