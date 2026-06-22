/*
 * Chapter 31 - Article Citations Test Driver
 *
 * Interactive harness that exercises the ArticleCitations class. It loops asking for a filename
 * (or "STOP" to quit), builds an ArticleCitations from the file, and passes it by value to
 * processCitations(), which prints the article line and every citation. The deliberate
 * pass-by-value copy is what triggers the copy constructor and copy() - the path where this stage
 * of the example exhibits its bug.
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
