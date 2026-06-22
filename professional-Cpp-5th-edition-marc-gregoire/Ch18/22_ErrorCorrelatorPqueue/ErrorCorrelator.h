/*
 * Chapter 18 - priority_queue Example: Error Correlator
 *
 * Stores Error objects in a std::priority_queue so the highest-priority error
 * is always served first, regardless of insertion order. push() adds an error,
 * top() reads the head, and pop() removes it. Priority comes from Error's
 * operator<=> (which yields operator< for the queue's default less comparator).
 *
 * Key notes:
 *   - priority_queue defaults to a vector and orders by operator<; top() is the
 *     "largest" element and pop() does not return it.
 *   - Header-only; included and exercised by ErrorCorrelatorTest.cpp.
 */

#pragma once

#include <queue>
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
	std::priority_queue<Error> m_errors;
};
