/*
 * Chapter 9 - Ref Qualifiers via Explicit Object Parameter (C++23)
 *
 * C++23 introduces the explicit object parameter (sometimes called "deducing this"):
 * the implicit `this` is replaced with an explicit first parameter whose type
 * carries the const-ness and value category of the object expression. This is a
 * cleaner way to express the same constraints as `&` / `&&` / `const &` qualifiers.
 *
 * Key notes:
 *   - `getText(this const TextHolder& self)` plays the role of the old
 *     `const string& getText() const &`.
 *   - `getText(this TextHolder&& self)` plays the role of `string&& getText() &&`.
 *   - You may freely call `self.m_text` - no `this->` necessary.
 *   - One member function template that takes `this auto&& self` can stand in for
 *     all four ref-qualified variants at once.
 *   - Requires `/std:c++latest` or a compiler with C++23 explicit-object-parameter
 *     support.
 *
 * Example:
 *     // Generic, deducing both const-ness and value category:
 *     decltype(auto) getText(this auto&& self) {
 *         return std::forward_like<decltype(self)>(self.m_text);
 *     }
 */
#include <print>
#include <string>
#include <utility>

using namespace std;

class TextHolder
{
public:
	explicit TextHolder(string text) : m_text{ move(text) } {}
	
	//const string& getText() const { return m_text; }
	
	const string& getText(this const TextHolder& self) { return self.m_text; }
	string&& getText(this TextHolder&& self) { return move(self.m_text); }

	TextHolder& operator=(this TextHolder& self, const string& rhs)
	{
		self.m_text = rhs;
		return self;
	}

private:
	string m_text;
};

TextHolder makeTextHolder()
{
	return TextHolder{ "Hello World!" };
}

int main()
{
	TextHolder textHolder{ "Hello world!" };
	println("{}", textHolder.getText());
	println("{}", TextHolder{ "Hello world!" }.getText());

	// Pointless, object is a temporary.
	//makeTextHolder() = "Pointless!";

	// Ok
	auto text{ makeTextHolder() };
	text = "Ok";
}
