/*
 * Chapter 11 - Modules (8/10): Driver
 *
 * Only `import math;` is needed. Trying to `import math:details;` from here
 * would be a compile error: partitions of a module can only be imported by
 * other parts of the same module.
 */
import math;

int main()
{
	auto a{ Math::lerchZeta(1, 2, 3) };
	auto b{ Math::superLog(1, 2) };
}
