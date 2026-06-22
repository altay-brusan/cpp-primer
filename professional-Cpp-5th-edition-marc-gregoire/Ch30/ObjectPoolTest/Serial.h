/*
 * Chapter 30 - A Small Test Subject for the Object Pool
 *
 * Serial is a minimal helper class used by the unit tests to verify the ObjectPool. Each
 * instance grabs the next value from a static counter on construction, so every Serial gets
 * a distinct serial number. The tests rely on this property to confirm that the pool hands
 * out distinct objects (testExclusivity) and that it correctly reuses the same underlying
 * storage after objects are released (testRelease). It is a good example of crafting simple,
 * observable types specifically to make a component's behavior easy to assert on.
 */
#pragma once

class Serial
{
public:
	// A new object gets a next serial number.
	Serial() : m_serialNumber{ ms_nextSerial++ } {}
	unsigned getSerialNumber() const { return m_serialNumber; }

private:
	static inline unsigned ms_nextSerial{ 0 }; // The first serial number is 0.
	unsigned m_serialNumber{ 0 };
};

