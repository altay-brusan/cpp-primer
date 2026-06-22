/*
 * Chapter 11 - File-scope static (driver side)
 *
 * Same shape as the anonymous-namespace sample, but the toggle in
 * AnotherFile.cpp is `static` instead of an anonymous namespace.
 *
 * As-shipped: AnotherFile.cpp declares `f()` with external linkage and
 * defines it - the link succeeds. Uncomment the `static void f();` line in
 * AnotherFile.cpp to convert it to internal linkage and watch the link
 * break.
 *
 * Both `static` and `namespace { ... }` achieve internal linkage. The
 * modern preference is the anonymous namespace - it works for types too,
 * not just functions and variables.
 */
void f();

int main()
{
	f();
}
