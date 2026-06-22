/*
 * Chapter 34 - Procedural C Networking Library (Stub Implementation)
 *
 * Minimal placeholder implementations of the networklib functions so the
 * mixing-C-and-C++ example compiles and runs. Real networking code is not
 * provided by the C or C++ Standard Library, so these stubs just allocate and
 * free dummy handles and return a fixed page. The point of the sample is the
 * C++ object-oriented wrapper around this procedural API, not the networking.
 */

#include "networklib.h"

/////////////////////////////////////////////////////////////////////
//                                                                 //
// For this example, these functions are kept to the bare minimum. //
//                                                                 //
/////////////////////////////////////////////////////////////////////

HostHandle* lookupHostByName(const char* hostName)
{
	return new HostHandle{};
}

void freeHostHandle(HostHandle* host)
{
	delete host;
}

ConnectionHandle* connectToHost(HostHandle* host)
{
	return new ConnectionHandle{};
}

void closeConnection(ConnectionHandle* connection)
{
	delete connection;
}

char* retrieveWebPage(ConnectionHandle* connection, const char* page)
{
	return new char[] { "Hello Webpage!" };
}

void freeWebPage(char* page)
{
	delete[] page;
}
