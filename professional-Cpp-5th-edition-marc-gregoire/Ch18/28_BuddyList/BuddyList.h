/*
 * Chapter 18 - multimap Example: Buddy Lists
 *
 * Stores a chat program's buddy lists in a multimap<string, string>, which
 * (unlike map) allows multiple values per key - here multiple buddies per user.
 * Declares add, remove, membership-test, and list-all operations; implemented
 * in BuddyList.cpp.
 *
 * Key notes:
 *   - multimap has no operator[]; all entries sharing a key are stored together
 *     and reached with lower_bound(), upper_bound(), or equal_range().
 */

#pragma once

#include <string>
#include <vector>
#include <map>

class BuddyList final
{
public:
	// Adds buddy as a friend of name.
	void addBuddy(const std::string& name, const std::string& buddy);

	// Removes buddy as a friend of name.
	void removeBuddy(const std::string& name, const std::string& buddy);

	// Returns true if buddy is a friend of name, false otherwise.
	bool isBuddy(const std::string& name, const std::string& buddy) const;

	// Retrieves a list of all the friends of name.
	std::vector<std::string> getBuddies(const std::string& name) const;

private:
	std::multimap<std::string, std::string> m_buddies;
};
