/*
 * Chapter 2 - C-Style Strings
 *
 * A C-style string is just an array of char terminated by a single NUL byte ('\0'). The
 * <cstring> functions (strcpy, strcat, strlen, ...) operate on these arrays directly and
 * never allocate memory for the caller. Always reserve strlen(src) + 1 bytes when copying
 * a C string - the +1 is the room for the trailing '\0'. copyString() below shows the
 * corrected allocation; appendStrings() generalizes the rule to a concatenation of three
 * inputs, where still only one extra byte is needed at the very end for the NUL.
 *
 * Key notes:
 *   - "hello" looks 5 characters long but needs 6 bytes in memory because of the '\0'.
 *   - NUL (one L, the '\0' terminator) is NOT the same thing as the NULL pointer.
 *   - strcpy() and strcat() do not check the destination size - they happily overflow.
 *     Allocate the exact right amount up front: strlen(s1)+strlen(s2)+strlen(s3)+1.
 *   - C strings still surface in C++ when talking to C libraries or OS APIs, so the rules
 *     remain relevant even when std::string is preferred for new code.
 *   - MSVC flags strcpy/strcat as unsafe (warning C4996); strcpy_s / strcat_s are the
 *     "secure C library" alternatives, but switching to std::string fixes the class of bug.
 *   - Caller of copyString()/appendStrings() must delete[] the returned buffer.
 *
 * Example:
 *     char* result{ new char[strlen(src) + 1] };  // +1 for '\0'
 *     strcpy(result, src);
 */

#include <print>
#include <cstring>

using namespace std;

#if defined(_MSC_VER)
	// Disable the following Microsoft Visual C++ warning for this example:
	// C4996: 'xyz': This function or variable may be unsafe. Consider using xyz_s instead.
	#pragma warning( disable : 4996)
#endif

char* copyString(const char* str)
{
	//char* result{ new char[strlen(str)] };  // BUG! Off by one!
	char* result{ new char[strlen(str) + 1] };
	strcpy(result, str);
	return result;
}

char* appendStrings(const char* str1, const char* str2, const char* str3)
{
	char* result{ new char[strlen(str1) + strlen(str2) + strlen(str3) + 1] };
	strcpy(result, str1);
	strcat(result, str2);
	strcat(result, str3);
	return result;
}

int main()
{
	const char* str1{ "Hello" };
	char* copy{ copyString(str1) };
	println("{}", copy);
	delete [] copy;
	copy = nullptr;

	const char* str2{ " World" };
	const char* str3{ "!" };
	char* result{ appendStrings(str1, str2, str3) };
	println("{}", result);
	delete [] result;
	result = nullptr;
}
