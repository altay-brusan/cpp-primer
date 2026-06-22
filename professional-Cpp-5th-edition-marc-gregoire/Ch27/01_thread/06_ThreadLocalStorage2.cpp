/*
 * Chapter 27 - thread_local Declaration Rules
 *
 * A compile-only reference showing where the thread_local specifier is and is not
 * allowed: at namespace scope (with internal or external linkage), on static class
 * data members, and on local variables (where it is implicitly static). A non-static
 * thread_local data member is illegal, as the commented-out line notes. main() is
 * empty; the file demonstrates declarations, not runtime behavior.
 */

static thread_local int x1; // OK, internal linkage (See Chapter 11)
thread_local int x2;        // OK, external linkage (See Chapter 11)

class Foo
{
	static thread_local int x3; // OK
	//thread_local int x4;      // Error!
};


void f()
{
	static thread_local int x5; // OK
	thread_local int x6;        // OK, implicitly static!
}

int main()
{
}
