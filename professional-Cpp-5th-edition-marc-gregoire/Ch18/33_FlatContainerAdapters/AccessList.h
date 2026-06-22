/*
 * Chapter 18 - flat_set Container Adapter
 *
 * The access control list reworked over a std::flat_set instead of a std::set.
 * flat_set (C++23) is a sorted associative adapter backed by a contiguous
 * sequence, offering the same interface as set with better cache locality for
 * lookups at the cost of slower insertions. The interface used here is
 * identical to the set version.
 *
 * Key notes:
 *   - Requires a C++23 toolchain with <flat_set> support.
 *   - Header-only; included and exercised by AccessListTest.cpp.
 */

#pragma once

#include <initializer_list>
#include <flat_set>
#include <string>
#include <string_view>
#include <vector>

class AccessList final
{
public:
	// Default constructor.
	AccessList() = default;

	// Constructor to support uniform initialization.
	AccessList(std::initializer_list<std::string_view> users)
	{
		m_allowed.insert(begin(users), end(users));
	}

	// Adds the user to the permissions list.
	void addUser(std::string user)
	{
		m_allowed.emplace(std::move(user));
	}

	// Removes the user from the permissions list.
	void removeUser(const std::string& user)
	{
		m_allowed.erase(user);
	}

	// Returns true if the user is in the permissions list.
	bool isAllowed(const std::string& user) const
	{
		return m_allowed.contains(user);
	}

	// Returns all the users who have permissions.
	const std::flat_set<std::string>& getAllUsers() const
	{
		return m_allowed;
	}

	// Returns a vector of all the users who have permissions.
	std::vector<std::string> getAllUsersAsVector() const
	{
		return { begin(m_allowed), end(m_allowed) };
	}

private:
	std::flat_set<std::string> m_allowed;
};
