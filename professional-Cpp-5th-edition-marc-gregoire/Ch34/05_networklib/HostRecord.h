/*
 * Chapter 34 - RAII Wrapper Around a C Handle (HostRecord)
 *
 * An object-oriented, RAII wrapper over the procedural networklib host-lookup
 * functions. Its constructor calls lookupHostByName() and stores the resulting
 * raw HostHandle in a std::unique_ptr whose custom deleter is freeHostHandle(),
 * so the C-allocated handle is released automatically. This shows how to give a
 * C library a safe, leak-free C++ interface when mixing the two languages.
 */

#pragma once

#include "networklib.h"
#include <memory>
#include <string>

// A class wrapping a HostHandle from the networklib library.
class HostRecord final
{
public:
	// Looks up the host record for the given host.
	explicit HostRecord(const std::string& host)
		: m_hostHandle{ lookupHostByName(host.c_str()), freeHostHandle }
	{ }

	// Returns the underlying handle.
	HostHandle* get() const noexcept { return m_hostHandle.get(); }

private:
	std::unique_ptr<HostHandle, decltype(&freeHostHandle)> m_hostHandle;
};
