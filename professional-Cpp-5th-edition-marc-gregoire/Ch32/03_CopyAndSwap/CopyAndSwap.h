/*
 * Chapter 32 - The Copy-and-Swap Idiom (syntax refresher)
 *
 * Declares a class skeleton that uses the copy-and-swap idiom to give its copy assignment
 * operator the strong (all-or-nothing) exception-safety guarantee. The interface pairs a
 * copy constructor and copy assignment operator with a noexcept swap() member function,
 * plus a standalone non-member swap() that simply forwards to the member version.
 *
 * Key notes:
 *   - The strong guarantee works because all the potentially throwing work happens on a
 *     temporary copy, and only a non-throwing swap commits the result.
 */
#pragma once

// A simple class that illustrates the copy-and-swap idiom.
class CopyAndSwap final
{
public:
	CopyAndSwap() = default;
	~CopyAndSwap();                                 // Destructor

	CopyAndSwap(const CopyAndSwap& src);            // Copy constructor
	CopyAndSwap& operator=(const CopyAndSwap& rhs); // Copy assignment operator

	void swap(CopyAndSwap& other) noexcept;         // noexcept swap() member function

private:
	// Private data members...
};

// Standalone noexcept swap() function
void swap(CopyAndSwap& first, CopyAndSwap& second) noexcept;
