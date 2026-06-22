/*
 * Chapter 29 - NameDB Second Attempt: std::map (Profiling)
 *
 * The header for the redesigned baby-name database, the profiler-driven response to the
 * slow vector version. It stores names in a std::map, which keeps entries sorted and
 * gives O(log n) lookups instead of O(n) scans. The two helpers that the profiler
 * showed were nearly identical, nameExists() and incrementNameCount(), are merged into
 * a single incrementIfExists() that finds and increments in one map lookup.
 *
 * Key notes:
 *   - Choosing a better data structure (design-level efficiency) is the real win here.
 */

#pragma once

#include <string>
#include <map>

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
	std::map<std::string, int> m_names;

	// Helper member functions
	bool incrementIfExists(const std::string& name);
	void addNewName(const std::string& name);
};
