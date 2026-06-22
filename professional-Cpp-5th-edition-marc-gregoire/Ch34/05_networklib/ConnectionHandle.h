/*
 * Chapter 34 - Opaque C Handle Type (ConnectionHandle)
 *
 * A bare placeholder for the connection data structure that the C networklib
 * returns from connectToHost(). Kept empty for the example; the WebHost RAII
 * class manages pointers to this type and releases them with closeConnection().
 */

#pragma once

///////////////////////////////////////////////////////////////
//                                                           //
// For this example, this class is kept to the bare minimum. //
//                                                           //
///////////////////////////////////////////////////////////////

class ConnectionHandle
{
};
