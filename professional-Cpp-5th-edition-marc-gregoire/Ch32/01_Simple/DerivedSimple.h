/*
 * Chapter 32 - Deriving from an Existing Class (syntax refresher)
 *
 * Shows how to extend a class by deriving from it. DerivedSimple publicly inherits from
 * Simple, chains to the base constructor, overrides publicMemberFunction() (calling the
 * base version via Simple::publicMemberFunction()), and adds a brand-new member function.
 *
 * Key notes:
 *   - "override" makes the compiler verify that the function really overrides a virtual
 *     base function, catching signature mismatches.
 *   - A derived class can still reach a base implementation with the Base::name() syntax.
 */
#pragma once

#include "Simple.h"

// A class derived from the Simple class.
class DerivedSimple : public Simple
{
public:
	DerivedSimple() : Simple{} // Constructor
	{ /* Implementation of constructor */ }

	void publicMemberFunction() override // Overridden member function
	{
		// Implementation of overridden member function
		Simple::publicMemberFunction(); // Access the base class implementation
	}

	virtual void anotherMemberFunction() // New member function
	{ /* Implementation of new member function */ }
};
