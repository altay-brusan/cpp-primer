/*
 * Chapter 10 - Subclass that customizes a private virtual hook
 *
 * The override here is `private` (same access as in the base). It works
 * because access checks happen at the *call site*. Inside `getMilesLeft()`
 * the call resolves through the vtable, lands on this 35-returning version,
 * and never goes through any public/private check on this class.
 */
#pragma once

#include "MilesEstimator.h"

class EfficientCarMilesEstimator : public MilesEstimator
{
private:
	int getMilesPerGallon() const override
	{
		return 35;
	}
};
