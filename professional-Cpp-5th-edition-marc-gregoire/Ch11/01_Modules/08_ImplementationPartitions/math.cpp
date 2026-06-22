/*
 * Chapter 11 - Modules (8/10): math implementation
 *
 * Implementation unit. `import :details;` brings in the helper - and because
 * `:details` is NOT re-exported from math.cppm, clients of `math` never see
 * `someHelperFunction`. That's a useful encapsulation tool: internal helpers
 * stay internal even though they live in their own translation unit.
 */
module math;

import :details;

double Math::superLog(double z, double b)
{
	// Implementation omitted...
	return someHelperFunction(z);
}

double Math::lerchZeta(double lambda, double alpha, double s)
{
	// Implementation omitted...
	return someHelperFunction(s);
}
