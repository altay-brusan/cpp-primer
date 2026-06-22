/*
 * Chapter 10 - The Template Method / Non-Virtual Interface Pattern
 *
 * MilesEstimator demonstrates the pattern where the public API is NOT virtual
 * but it internally calls a virtual hook that subclasses override. The base
 * class defines *the algorithm* (`miles = mpg * gallons`), and subclasses only
 * customize *one piece* of it (the mpg value).
 *
 * Key notes:
 *   - `getMilesLeft()` is the stable public entry point. Callers don't have to
 *     know which subclass is being used.
 *   - `getMilesPerGallon()` is a *private* virtual member. Subclasses can
 *     still override it (yes, even though it's private! - access is checked
 *     at the call site, not at override time). This is the Non-Virtual
 *     Interface (NVI) idiom.
 *   - Why private virtuals? Subclasses can swap *implementation* without
 *     getting access to *invocation*. The base class controls when the hook
 *     fires; the subclass controls what it does.
 *   - The EfficientCarMilesEstimator subclass shows this in 3 short lines.
 */
#pragma once

class MilesEstimator
{
public:
	virtual ~MilesEstimator() = default;

	int getMilesLeft() const                           // non-virtual public API
	{
		return getMilesPerGallon() * getGallonsLeft();
	}

	virtual void setGallonsLeft(int gallons)
	{
		m_gallonsLeft = gallons;
	}

	virtual int getGallonsLeft() const
	{
		return m_gallonsLeft;
	}

private:
	int m_gallonsLeft{ 0 };

	virtual int getMilesPerGallon() const              // the customization hook
	{
		return 20;
	}
};
