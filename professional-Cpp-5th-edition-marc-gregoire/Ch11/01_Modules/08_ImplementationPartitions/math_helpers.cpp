/*
 * Chapter 11 - Modules (8/10): math:details implementation partition
 *
 * `module math:details;` (no `export`) declares an implementation partition.
 * It lives inside the math module's name scope but isn't accessible to
 * external importers - only other parts of `math` can import it.
 */
module math:details;  // math:details implementation partition

double someHelperFunction(double a)
{
	// Implementation omitted...
	return 42;
}
