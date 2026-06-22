/*
 * Chapter 11 - Modules (8/10): Implementation Partitions
 *
 * `math` exports two functions but keeps the implementation helpers hidden
 * via an *implementation partition*. The partition `math:details` is not
 * imported by the primary interface, so clients can't reach
 * `someHelperFunction`.
 *
 * Files in this sample:
 *   - math.cppm           - primary interface unit (this file).
 *   - math.cpp            - implementation unit of `math`, imports :details.
 *   - math_helpers.cpp    - the `math:details` implementation partition.
 */
export module math; // math module declaration

export namespace Math
{
	double superLog(double z, double b);
	double lerchZeta(double lambda, double alpha, double s);
}
