/*
 * Chapter 33 - Dependency Injection: Logger Implementation
 *
 * Implementation for Logger.h - see the header for the conceptual notes.
 * Opens the log file in append mode, formats each entry with a timestamp and
 * log-level string, and skips messages below the configured level.
 */

#include "Logger.h"
#include <print>
#include <chrono>
#include <stdexcept>
#include <ostream>

using namespace std;

Logger::Logger(const string& logFilename)
{
	m_outputStream.open(logFilename, ios_base::app);
	if (!m_outputStream.good()) {
		throw runtime_error{ "Unable to initialize the Logger!" };
	}
	println(m_outputStream, "{}: Logger started.", chrono::system_clock::now());
}

void Logger::setLogLevel(LogLevel level)
{
	m_logLevel = level;
}

string_view Logger::getLogLevelString(LogLevel level) const
{
	switch (level) {
	case LogLevel::Debug: return "DEBUG";
	case LogLevel::Info: return "INFO";
	case LogLevel::Error: return "ERROR";
	}
	throw runtime_error{ "Invalid log level." };
}

void Logger::log(string_view message, LogLevel logLevel)
{
	if (m_logLevel > logLevel) {
		return;
	}

	println(m_outputStream, "{}: [{}] {}", chrono::system_clock::now(),
		getLogLevelString(logLevel), message);
}
