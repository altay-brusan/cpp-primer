/*
 * Chapter 34 - Opaque C Handle Type (HostHandle)
 *
 * A bare placeholder for the host data structure that the C networklib hands
 * back from lookupHostByName(). In a real C library this would be an opaque
 * record; here it is kept empty so the mixing-C-and-C++ example builds. The
 * HostRecord RAII class wraps pointers to this type.
 */

#pragma once

///////////////////////////////////////////////////////////////
//                                                           //
// For this example, this class is kept to the bare minimum. //
//                                                           //
///////////////////////////////////////////////////////////////

class HostHandle
{
};
