/*
 * Chapter 21 - Wide Characters and Wide Streams
 *
 * Demonstrates the wchar_t built-in type for holding a wide character that can
 * represent non-ASCII alphabets (Japanese, Arabic, and so on) that do not fit in
 * a single 8-bit char. Wide character and string literals are written with an L
 * prefix (L'm'), and output goes through the wide stream wcout instead of cout.
 * The example also shows the wide overload of std::format, which produces a
 * std::wstring when given a wide format string.
 *
 * Key notes:
 *   - The C++ standard does not fix the size of wchar_t (16 bits on Windows,
 *     often 32 bits elsewhere), so do not assume a particular width in portable code.
 *   - Wide versions exist for most types: wstring, wcout, wcin, wofstream, etc.
 */

#include <iostream>
#include <format>

using namespace std;

int main()
{
	wchar_t myWideCharacter{ L'm' };
	wcout << L"I am a wide-character string literal." << endl;
	wcout << format(L"myWideCharacter is {}", myWideCharacter) << endl;
}
