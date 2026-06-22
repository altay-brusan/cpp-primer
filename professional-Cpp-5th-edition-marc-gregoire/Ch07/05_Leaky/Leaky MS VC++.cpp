/*
 * Chapter 7 - Finding and Fixing Memory Leaks in Windows with Visual C++
 *
 * The Visual C++ CRT (C Run-Time) library can detect leaked allocations and print the
 * source file and line where each leak was allocated. Enabling it requires three things,
 * all shown below: define `_CRTDBG_MAP_ALLOC` BEFORE the headers, redefine `new` as
 * `DBG_NEW` under `_DEBUG` so allocations carry file/line metadata, and call
 * `_CrtSetDbgFlag(...)` early in `main()` so the runtime dumps leaks at exit.
 *
 * Key notes:
 *   - The redefinition is wrapped in `#ifdef _DEBUG` because the bookkeeping has a perf
 *     cost; release builds disable it.
 *   - Output lines look like `leaky.cpp(33) : {146} normal block at 0x..., 4 bytes long.`
 *     Double-click the line in the VS output window to jump straight to the allocation.
 *   - `_CrtSetBreakAlloc(N)` makes the debugger break exactly when allocation number N
 *     happens - handy when a leak number is stable across runs.
 *   - On Linux, Valgrind plays the equivalent role; on any platform, AddressSanitizer
 *     (`-fsanitize=address`) is another excellent option.
 */

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
	#ifndef DBG_NEW
		#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
		#define new DBG_NEW
	#endif
#endif  // _DEBUG

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
	outSimplePtr = new Simple{}; // BUG! Doesn't delete the original.
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);  // dump leaks on exit

	Simple* simplePtr{ new Simple{} }; // Allocate a Simple object.

	doSomething(simplePtr);

	delete simplePtr; // Only cleans up the second object.
}
