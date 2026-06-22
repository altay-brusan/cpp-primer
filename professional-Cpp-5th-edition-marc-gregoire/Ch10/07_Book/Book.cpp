/*
 * Chapter 10 - Chaining Through Multiple Levels of Inheritance
 *
 * `Romance` inherits from `Paperback` inherits from `Book`. Each override
 * builds on the parent's by calling it explicitly with a qualified name. This
 * is the idiomatic way to *extend* (not replace) inherited behavior - the
 * derived class adds its prefix and delegates the rest upstream.
 *
 * Key notes:
 *   - `Paperback::getDescription()` calls `Book::getDescription()` and prepends
 *     "Paperback ". `Romance::getDescription()` calls `Paperback::...` and
 *     prepends "Romance ". The chain unwinds left-to-right in the output.
 *   - `Romance::getHeight()` shows partial reuse: it doesn't return a hardcoded
 *     number, it reads `Paperback::getHeight()` and adjusts. If Paperback ever
 *     changes its height, Romance follows.
 *   - The class qualifier (`Book::`, `Paperback::`) bypasses virtual dispatch -
 *     it's how you say "the version I inherited, not whichever override the
 *     runtime would pick".
 *   - Technical never appears in main(); it's there to show the shape generalizes.
 */
#include <print>
#include <string>

using namespace std;

class Book
{
public:
	virtual ~Book() = default;
	virtual string getDescription() const { return "Book"; }
	virtual int getHeight() const { return 120; }
};

class Paperback : public Book
{
public:
	string getDescription() const override {
		return "Paperback " + Book::getDescription();   // delegate up, prepend our piece
	}
};

class Romance : public Paperback
{
public:
	string getDescription() const override {
		return "Romance " + Paperback::getDescription();
	}
	int getHeight() const override { return Paperback::getHeight() / 2; }
};

class Technical : public Book
{
public:
	string getDescription() const override {
		return "Technical " + Book::getDescription();
	}
};

int main()
{
	Romance novel;
	Book book;
	println("{}", novel.getDescription()); // Outputs "Romance Paperback Book"
	println("{}", book.getDescription());  // Outputs "Book"
	println("{}", novel.getHeight());      // Outputs "60"
	println("{}", book.getHeight());       // Outputs "120"
}
