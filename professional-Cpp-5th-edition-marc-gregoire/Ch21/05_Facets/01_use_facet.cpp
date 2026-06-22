/*
 * Chapter 21 - Using Facets
 *
 * Demonstrates std::use_facet(), which extracts an individual facet (one cultural
 * component of a locale) from a locale object. Here it retrieves the monetary
 * punctuation facet moneypunct<wchar_t> for both the US and Great Britain locales
 * and calls curr_symbol() to obtain each region's currency symbol, which is then
 * printed to wcout.
 *
 * Key notes:
 *   - The innermost template type (wchar_t) selects the character type of the facet.
 *   - The British pound symbol may render as a question mark or box depending on
 *     the console configuration.
 */

#include <iostream>
#include <locale>
#include <string>

using namespace std;

int main()
{
	locale locUSEng{ "en-US" };       // For Windows
	//locale locUSEng{ "en_US" };     // For Linux
	locale locBritEng{ "en-GB" };     // For Windows
	//locale locBritEng{ "en_GB" };   // For Linux

	wstring dollars{ use_facet<moneypunct<wchar_t>>(locUSEng).curr_symbol() };
	wstring pounds{ use_facet<moneypunct<wchar_t>>(locBritEng).curr_symbol() };

	wcout << L"In the US, the currency symbol is " << dollars << endl;
	wcout << L"In Great Britain, the currency symbol is " << pounds << endl;
}
