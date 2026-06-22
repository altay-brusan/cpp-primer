/*
 * Chapter 33 - Decorator Pattern
 *
 * Demonstrates the Decorator pattern for dynamically adding behavior to objects.
 * BoldParagraph and ItalicParagraph both implement the IParagraph interface and
 * wrap another IParagraph, augmenting its getHTML() output with surrounding tags.
 * Because each decorator both is-a and has-a IParagraph, decorators can be nested
 * (italic wrapping bold wrapping plain text) to compose behavior at run time
 * without subclassing every combination.
 *
 * Key notes:
 *   - Each decorator holds a reference to the IParagraph it wraps.
 *   - Contains main(); run as a standalone program.
 */

#include <print>
#include <string>
#include <utility>
#include <format>

using namespace std;

class IParagraph
{
public:
	virtual ~IParagraph() = default;  // Always a virtual destructor!
	virtual std::string getHTML() const = 0;
};

class Paragraph : public IParagraph
{
public:
	explicit Paragraph(std::string text) : m_text{ std::move(text) } {}
	std::string getHTML() const override { return format("<p>{}</p>", m_text); }

private:
	std::string m_text;
};

class BoldParagraph : public IParagraph
{
public:
	explicit BoldParagraph(const IParagraph& paragraph) : m_wrapped{ paragraph } { }

	std::string getHTML() const override
	{
		return format("<b>{}</b>", m_wrapped.getHTML());
	}

private:
	const IParagraph& m_wrapped;
};

class ItalicParagraph : public IParagraph
{
public:
	explicit ItalicParagraph(const IParagraph& paragraph) : m_wrapped{ paragraph } { }

	std::string getHTML() const override
	{
		return format("<i>{}</i>", m_wrapped.getHTML());
	}

private:
	const IParagraph& m_wrapped;
};



int main()
{
	Paragraph text{ "A party? For me? Thanks!" };

	// Bold
	println("{}", BoldParagraph{ text }.getHTML());

	// Bold and Italic
	println("{}", ItalicParagraph{ BoldParagraph{ text } }.getHTML());
}
