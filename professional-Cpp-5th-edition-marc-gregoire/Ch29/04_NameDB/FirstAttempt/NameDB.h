/*
 * Chapter 29 - NameDB First Attempt: vector of pairs (Profiling)
 *
 * The header for the deliberately inefficient first design of the baby-name database.
 * It stores names in a std::vector of name/count pairs, so every lookup, increment,
 * and rank query is a linear O(n) scan. With hundreds of thousands of names this is
 * the bottleneck a profiler is meant to expose, motivating the map-based redesigns in
 * the SecondAttempt and ThirdAttempt folders.
 *
 * Key notes:
 *   - This is the slow baseline kept intentionally for profiling comparison.
 */

#pragma once

#include <string>
#include <vector>
#include <utility>

class NameDB
{
public:
	// Reads list of baby names in nameFile to populate the database.
	// Throws invalid_argument if nameFile cannot be opened or read.
	explicit NameDB(const std::string& nameFile);

	// Returns the rank of the name (1st, 2nd, etc).
	// Returns -1 if the name is not found.
	int getNameRank(const std::string& name) const;

	// Returns the number of babies with a given name.
	// Returns -1 if the name is not found.
	int getAbsoluteNumber(const std::string& name) const;

private:
	std::vector<std::pair<std::string, int>> m_names;

	// Helper member functions
	bool nameExists(const std::string& name) const;
	void incrementNameCount(const std::string& name);
	void addNewName(const std::string& name);
};
