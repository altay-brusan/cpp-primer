/*
 * Chapter 32 - Writing a Class from Scratch
 *
 * Implementation for Simple.h - see the header for the conceptual notes.
 * The constructor uses a ctor-initializer to set m_publicInteger; the member functions
 * are empty stubs that simply demonstrate the out-of-class definition syntax.
 */
#include "Simple.h"

Simple::Simple() : m_publicInteger{ 40 }
{
	// Implementation of constructor
}

void Simple::publicMemberFunction() { /* Implementation */ }

void Simple::protectedMemberFunction() { /* Implementation */ }

void Simple::privateMemberFunction() { /* Implementation */ }
