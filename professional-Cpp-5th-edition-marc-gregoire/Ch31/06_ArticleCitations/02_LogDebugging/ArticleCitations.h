/*
 * Chapter 31 - Article Citations Worked Example (class interface)
 *
 * Declares the ArticleCitations class used as the chapter's step-by-step debugging case study.
 * It reads a citations file - first line is the article info, then citations one per line - storing
 * the article in a std::string and the citations in a raw C-style array of std::string. The
 * deliberately poor design (raw owning pointer, int counts, manual copy and assignment) is what
 * makes it a good vehicle for demonstrating memory and stream-state bugs and how to track them down.
 *
 * Key notes:
 *   - Because it owns m_citations via a raw pointer, the class needs a destructor, copy
 *     constructor, and copy-assignment operator; bugs in these are central to the example.
 *   - Real code should use a Standard Library container and the rule of zero instead.
 */

#pragma once

#include <string>

class ArticleCitations
{
public:
	explicit ArticleCitations(const std::string& filename);
	virtual ~ArticleCitations();
	ArticleCitations(const ArticleCitations& src);
	ArticleCitations& operator=(const ArticleCitations& rhs);

	const std::string& getArticle() const;
	int getNumCitations() const;
	const std::string& getCitation(int i) const;

private:
	void readFile(const std::string& filename);
	void copy(const ArticleCitations& src);

	std::string m_article;
	std::string* m_citations{ nullptr };
	int m_numCitations{ 0 };
};
