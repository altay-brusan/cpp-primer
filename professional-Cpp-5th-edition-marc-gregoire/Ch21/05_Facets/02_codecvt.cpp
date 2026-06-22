/*
 * Chapter 21 - Encoding Conversion with the codecvt Facet
 *
 * Demonstrates the codecvt facet, which converts between character encodings. The
 * code obtains codecvt<wchar_t, char, mbstate_t> from the user's locale and uses
 * its in() method to convert a narrow (char) string into a wide (wchar_t) string,
 * tracking conversion state through an mbstate_t object and the fromNext and toNext
 * pointers. The wide result is then resized to the actually converted length and
 * printed to wcout.
 *
 * Key notes:
 *   - These codecvt facets are notoriously low-level and awkward to use directly.
 *   - The convenience wrappers in <codecvt> (wstring_convert, etc.) were deprecated
 *     in C++17; the book recommends a third-party library such as ICU instead.
 */

#include <iostream>
#include <locale>
#include <codecvt>
#include <string>

using namespace std;

int main()
{
	auto& facet{ use_facet<codecvt<wchar_t, char, mbstate_t>>(locale{ }) };
	string narrowString{ "Hello" };
	mbstate_t mb{};
	wstring wideString(narrowString.size(), '\0');
	const char* fromNext{ nullptr };
	wchar_t* toNext{ nullptr };
	facet.in(mb, narrowString.data(), narrowString.data() + narrowString.size(), fromNext,
		wideString.data(), wideString.data() + wideString.size(), toNext);
	wideString.resize(toNext - wideString.data());
	wcout << wideString << endl;
}
