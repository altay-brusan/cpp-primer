/*
 * Chapter 33 - Dependency Injection: the ILogger Interface
 *
 * Declares the abstract ILogger interface used by the Dependency Injection
 * example. Rather than a class creating its own logger, code depends only on
 * this pure-virtual interface and receives a concrete logger from the outside.
 * This decouples a component from any specific logging implementation and makes
 * it easy to swap loggers (or inject a mock) without touching the dependent code.
 *
 * Key notes:
 *   - All methods are pure virtual and the destructor is virtual, as required
 *     for a polymorphic base class.
 *   - LogLevel lets callers filter which messages are actually written.
 */

#pragma once

#include <string_view>

// Definition of a logger interface.
class ILogger
{
public:
	// Virtual destructor.
	virtual ~ILogger() = default;

	// Enumeration for the different log levels.
	enum class LogLevel {
		Debug,
		Info,
		Error
	};

	// Sets the log level.
	virtual void setLogLevel(LogLevel level) = 0;

	// Logs a single message at the given log level.
	virtual void log(std::string_view message, LogLevel logLevel) = 0;
};
