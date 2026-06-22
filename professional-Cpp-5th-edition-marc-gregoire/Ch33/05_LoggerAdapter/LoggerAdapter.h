/*
 * Chapter 33 - Adapter Pattern: Interfaces and Adapter
 *
 * Declares the types for the Adapter pattern example. An existing Logger (with a
 * log(level, message) signature) needs to be used through a different, simpler
 * IAdaptedLogger interface that exposes only log(message). AdaptedLogger is the
 * adapter: it implements the desired IAdaptedLogger interface while holding a
 * Logger instance internally and translating calls to it, bridging the two
 * incompatible interfaces.
 *
 * Key notes:
 *   - ILogger and Logger model the pre-existing functionality being adapted.
 *   - AdaptedLogger owns a Logger member and forwards each adapted call to it.
 */

#pragma once

#include <string>
#include <string_view>

// Definition of a logger interface.
class ILogger
{
public:
	virtual ~ILogger() = default;  // Always a virtual destructor!

	enum class LogLevel {
		Debug,
		Info,
		Error
	};

	// Logs a single message at the given log level.
	virtual void log(LogLevel level, const std::string& message) = 0;
};


// Concrete implementation of ILogger.
class Logger : public ILogger
{
public:
	Logger();

	void log(LogLevel level, const std::string& message) override;

private:
	// Converts a log level to a human readable string.
	std::string_view getLogLevelString(LogLevel level) const;
};



// Adapted logger interface.
class IAdaptedLogger
{
public:
	virtual ~IAdaptedLogger() = default;  // Always a virtual destructor!
	// Logs a single message with Info as log level.
	virtual void log(std::string_view message) = 0;
};



// Implementation of adapted logger.
class AdaptedLogger : public IAdaptedLogger
{
public:
	AdaptedLogger();
	void log(std::string_view message) override;

private:
	Logger m_logger;
};
