/*
 * Chapter 34 - Procedural C Networking Library (Interface)
 *
 * Declares a small, non-object-oriented C-style API for looking up a host,
 * connecting to it, and retrieving a web page, plus the matching free
 * functions. It stands in for legacy or third-party C code that a C++ program
 * must consume. This header is the procedural interface that the HostRecord and
 * WebHost RAII classes wrap to give it an object-oriented, const-correct,
 * exception-safe face (the facade pattern for mixing C and C++).
 */

#pragma once

#include "HostHandle.h"
#include "ConnectionHandle.h"

// Gets the host record for a particular Internet host given
// its hostname (i.e. www.host.com).
HostHandle* lookupHostByName(const char* hostName);
// Frees the given HostHandle.
void freeHostHandle(HostHandle* host);

// Connects to the given host.
ConnectionHandle* connectToHost(HostHandle* host);
// Closes the given connection.
void closeConnection(ConnectionHandle* connection);

// Retrieves a web page from an already-opened connection.
char* retrieveWebPage(ConnectionHandle* connection, const char* page);
// Frees the memory pointed to by page.
void freeWebPage(char* page);
