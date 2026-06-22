/*
 * Chapter 33 - Singleton Pattern: the Logger Class
 *
 * Declares a Singleton Logger - a class with exactly one shared instance. The
 * constructor and destructor are private, copy and move operations are deleted,
 * and the single instance is obtained through the static instance() accessor.
 * setLogFilename() configures the file before the instance is first created.
 *
 * Key notes:
 *   - instance() returns a reference to a function-local static, giving lazy,
 *     thread-safe initialization on first use.
 *   - Deleting the copy and move operations prevents accidental duplication.
 *   - ms_logFilename is a static inline member that must be set before the
 *     first instance() call.
 */

#pragma once

#include <fstream>
#include <string>
#include <string_view>

// Definition of a singleton logger class.
class Logger final
{
public:
	enum class LogLevel {
		Debug,
		Info,
		Error
	};

	// Sets the name of the log file.
	// Note: needs to be called before the first call to instance()!
	static void setLogFilename(std::string logFilename);

	// Returns a reference to the singleton Logger object.
	static Logger& instance();

	// Prevent copy/move construction.
	Logger(const Logger&) = delete;
	Logger(Logger&&) = delete;

	// Prevent copy/move assignment operations.
	Logger& operator=(const Logger&) = delete;
	Logger& operator=(Logger&&) = delete;

	// Sets the log level.
	void setLogLevel(LogLevel level);

	// Logs a single message at the given log level.
	void log(std::string_view message, LogLevel logLevel);

private:
	// Private constructor and destructor.
	Logger();
	~Logger();

	// Converts a log level to a human readable string.
	std::string_view getLogLevelString(LogLevel level) const;

	static inline std::string ms_logFilename;
	std::ofstream m_outputStream;
	LogLevel m_logLevel{ LogLevel::Error };
};
