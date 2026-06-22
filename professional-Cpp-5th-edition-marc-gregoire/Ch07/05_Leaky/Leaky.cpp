/*
 * Chapter 7 - Memory Leaks
 *
 * A memory leak happens when a `new`-allocated resource loses its last owner without
 * `delete` being called. The classic shape, illustrated here, is a function that takes a
 * pointer by reference and overwrites it with a fresh allocation - the original pointee
 * becomes orphaned forever. Once the only pointer to an object is overwritten or goes out
 * of scope, that memory cannot be reclaimed for the rest of the program's lifetime.
 *
 * Key notes:
 *   - The `Simple` class itself is exception-correct (it deletes `m_intPtr` in its dtor)
 *     yet the program still leaks - the bug lives in the caller, not the class.
 *   - `Simple*&` (reference-to-pointer) is a yellow flag in an API: callers often miss
 *     that the function reassigns their variable.
 *   - In modern code both `m_intPtr` and `simplePtr` should be smart pointers; `unique_ptr`
 *     would have deleted the original automatically on assignment.
 *   - Even a single `delete` paired with each `new` is not enough if early returns or
 *     thrown exceptions skip the `delete` - this motivates RAII.
 */

class Simple
{
public:
	Simple() { m_intPtr = new int{}; }
	~Simple() { delete m_intPtr; }

	void setValue(int value) { *m_intPtr = value; }

private:
	int* m_intPtr;
};

void doSomething(Simple*& outSimplePtr)
{
	outSimplePtr = new Simple{}; // BUG! Overwrites the caller's pointer without deleting it.
}

int main()
{
	Simple* simplePtr{ new Simple{} }; // Allocate a Simple object - this one will leak.

	doSomething(simplePtr);            // Caller's pointer now refers to a NEW object;
	                                   // the first one is orphaned with no way to reach it.

	delete simplePtr; // Only cleans up the second object - first one is leaked forever.
}
