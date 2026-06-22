/*
 * Chapter 32 - The Copy-and-Swap Idiom
 *
 * Implementation for CopyAndSwap.h - see the header for the conceptual notes.
 * The copy assignment operator makes a local copy of the source, then commits with the
 * noexcept swap(); swap() brings std::swap into scope with a using-declaration so that
 * each data member can be swapped via the best available swap overload.
 */
#include "CopyAndSwap.h"
#include <utility>

CopyAndSwap::~CopyAndSwap() { /* Implementation of destructor. */ }

CopyAndSwap::CopyAndSwap(const CopyAndSwap& src)
{
	// This copy constructor can first delegate to a non-copy constructor
	// if any resource allocations have to be done. See the Spreadsheet
	// implementation in Chapter 9 for an example.

	// Make a copy of all data members...
}

void swap(CopyAndSwap& first, CopyAndSwap& second) noexcept
{
	first.swap(second);
}

void CopyAndSwap::swap(CopyAndSwap& other) noexcept
{
	using std::swap;

	// Swap each data member, for example:
	// swap(m_data, other.m_data);
}

CopyAndSwap& CopyAndSwap::operator=(const CopyAndSwap& rhs)
{
	// Copy-and-swap idiom.
	auto copy{ rhs };  // Do all the work in a temporary instance.
	swap(copy);        // Commit the work with only non-throwing operations.
	return *this;
}
