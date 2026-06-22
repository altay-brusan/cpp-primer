/*
 * Chapter 18 - stack Example: Error Correlator
 *
 * The same ErrorCorrelator as the priority_queue version, but backed by a
 * std::stack for last-in first-out (LIFO) order, so the most recently added
 * error is served first. Only the member type changes; push(), top(), pop(),
 * and empty() exist on both adapters, so the method bodies are identical.
 *
 * Key notes:
 *   - stack defaults to a deque; top() and pop() act on the most recently
 *     pushed element, and pop() does not return it.
 *   - Header-only; included and exercised by ErrorCorrelatorTest.cpp.
 */

#pragma once

#include <stack>
#include <string>
#include <compare>
#include <iostream>
#include <stdexcept>

// Sample Error class with just a priority and a string error description.
class Error final
{
public:
	explicit Error(int priority, std::string errorString)
		: m_priority{ priority }, m_errorString{ std::move(errorString) } { }
	int getPriority() const { return m_priority; }
	const std::string& getErrorString() const { return m_errorString; }
	// Compare Errors according to their priority.
	auto operator<=>(const Error& rhs) const { return getPriority() <=> rhs.getPriority(); }

private:
	int m_priority;
	std::string m_errorString;
};

// Stream insertion overload for Errors.
inline std::ostream& operator<<(std::ostream& os, const Error& err)
{
	std::print(os, "{} (priority {})", err.getErrorString(), err.getPriority());
	return os;
}

// Simple ErrorCorrelator class that returns highest priority errors first.
class ErrorCorrelator final
{
public:
	// Add an error to be correlated.
	void addError(const Error& error) { m_errors.push(error); }

	// Retrieve the next error to be processed.
	[[nodiscard]] Error getError()
	{
		// If there are no more errors, throw an exception.
		if (m_errors.empty()) {
			throw std::out_of_range{ "No more errors." };
		}
		// Save the top element.
		Error top{ m_errors.top() };
		// Remove the top element.
		m_errors.pop();
		// Return the saved element.
		return top;
	}
private:
	std::stack<Error> m_errors;
};
