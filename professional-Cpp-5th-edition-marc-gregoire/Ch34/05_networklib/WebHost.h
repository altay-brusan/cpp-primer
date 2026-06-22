/*
 * Chapter 34 - Object-Oriented Facade Over a C Library (WebHost)
 *
 * The higher-level RAII class that captures the common usage pattern of the
 * procedural networklib: look up a host, open a connection, and fetch pages.
 * It uses HostRecord internally, holds the ConnectionHandle in a unique_ptr
 * with closeConnection() as deleter, and getPage() wraps the C-allocated page
 * buffer so it is freed with freeWebPage() and returned as a std::string. This
 * is the facade that hides the C library's complexity and const-incorrectness.
 */

#pragma once

#include "networklib.h"
#include "HostRecord.h"

// A class wrapping a ConnectionHandle from the networklib library.
class WebHost final
{
public:
	// Connects to the given host.
	explicit WebHost(const std::string& host);

	// Obtains the given page from this host.
	std::string getPage(const std::string& page);
private:
	std::unique_ptr<ConnectionHandle, decltype(&closeConnection)> m_connection{ nullptr, closeConnection };
};

WebHost::WebHost(const std::string& host)
{
	HostRecord hostRecord{ host };
	if (hostRecord.get()) {
		m_connection = { connectToHost(hostRecord.get()), closeConnection };
	}
}

std::string WebHost::getPage(const std::string& page)
{
	std::string resultAsString;
	if (m_connection) {
		std::unique_ptr<char[], decltype(&freeWebPage)> result{
			retrieveWebPage(m_connection.get(), page.c_str()),
			freeWebPage };
		resultAsString = result.get();
	}
	return resultAsString;
}
