/*
 * Chapter 31 - Article Citations Test Driver
 *
 * Interactive harness that exercises the ArticleCitations class. It loops asking for a filename
 * (or "STOP" to quit), builds an ArticleCitations from the file, and passes it by value to
 * processCitations(), which prints the article line and every citation. With the final corrected
 * implementation, both a normal file (paper1.txt) and a file with no citations (paper2.txt) are
 * handled without crashing.
 *
 * Key notes:
 *   - Needs ArticleCitations.cpp from the same folder and reads a filename from stdin plus the
 *     paper1.txt / paper2.txt data files; it does not run unattended.
 */

#include "ArticleCitations.h"
#include <print>
#include <iostream>

using namespace std;

void processCitations(ArticleCitations cit)
{
	println("{}", cit.getArticle());
	for (int i{ 0 }; i < cit.getNumCitations(); ++i) {
		println("{}", cit.getCitation(i));
	}
}

int main()
{
	while (true) {
		print("Enter a file name (\"STOP\" to stop): ");
		string filename;
		cin >> filename;
		if (filename == "STOP") { break; }

		ArticleCitations cit{ filename };
		processCitations(cit);
	}
}
