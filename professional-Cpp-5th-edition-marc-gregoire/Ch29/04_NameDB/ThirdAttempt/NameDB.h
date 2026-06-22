/*
 * Chapter 29 - NameDB Third Attempt: streamlined map (Profiling)
 *
 * The header for the final, leanest version of the baby-name database. It still uses a
 * std::map, but the helper member functions are gone entirely: the constructor now
 * populates the map with the single idiom ++m_names[name], which inserts a
 * zero-initialized entry on first sight and increments it thereafter. The interface
 * keeps only the public query member functions.
 *
 * Key notes:
 *   - Fewer lookups and less code than the second attempt, same O(log n) complexity.
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
};
