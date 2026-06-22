/*
 * Chapter 19 - Function Pointers into a Dynamic Link Library
 *
 * A real-world use of function pointers: obtaining the address of a function from a
 * Windows DLL at run time. LoadLibraryA() loads User32.dll, GetProcAddress() looks up
 * the MessageBoxA symbol, and the result is cast to a typed function pointer
 * (MessageBoxFunction) so it can be called like a normal function. Both calls are checked
 * for failure before use.
 *
 * Key notes:
 *   - Windows-specific (Windows.h, LoadLibraryA, GetProcAddress); not portable and only
 *     builds and runs on Windows.
 */
#include <Windows.h>
#include <print>

using namespace std;

int main()
{
	HMODULE lib{ ::LoadLibraryA("User32.dll") };
	if (!lib) {
		println("Unable to load User32.dll.");
		return 1;
	}

	using MessageBoxFunction = int(*)(HWND, LPCSTR, LPCSTR, UINT);
	MessageBoxFunction messageBox{ (MessageBoxFunction)::GetProcAddress(lib, "MessageBoxA") };
	if (!messageBox) {
		println("Unable to get the address of MessageBoxA().");
		return 2;
	}

	messageBox(NULL, "Hello World!", "ProC++", MB_OK);
}
