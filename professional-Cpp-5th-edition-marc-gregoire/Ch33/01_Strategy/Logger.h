/*
 * Chapter 33 - Dependency Injection: a Concrete Logger
 *
 * Declares Logger, a concrete file-based implementation of the ILogger
 * interface. In the Dependency Injection pattern this concrete type is created
 * by the application and handed to the components that need logging; those
 * components only ever see the ILogger interface, so the concrete logger can be
 * replaced freely.
 *
 * Key notes:
 *   - Writes to an std::ofstream opened in append mode.
 *   - Holds a current LogLevel so messages below the threshold are dropped.
 */

#pragma once

#include "ILogger.h"
#include <fstream>
#include <string>

class Logger : public ILogger
{
public:
	explicit Logger(const std::string& logFilename);
	void setLogLevel(LogLevel level) override;
	void log(std::string_view message, LogLevel logLevel) override;

private:
	// Converts a log level to a human readable string.
	std::string_view getLogLevelString(LogLevel level) const;

	std::ofstream m_outputStream;
	LogLevel m_logLevel{ LogLevel::Error };
};
