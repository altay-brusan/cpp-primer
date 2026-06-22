/*
 * Chapter 9 - Ref-Qualified Member Functions
 *
 * Add `&` or `&&` after a member function's signature to constrain the kind of
 * object expression it can be called on - `&` restricts to lvalue instances,
 * `&&` to rvalue instances (temporaries or the result of `std::move`). Combine
 * the two and you can offer cheap moves for the temporary case while still
 * returning safe references for ordinary usage.
 *
 * Key notes:
 *   - `const string& getText() const &` is the lvalue overload - returns a
 *     reference into the live object.
 *   - `string&& getText() &&` is the rvalue overload - returns an rvalue
 *     reference, so the caller can move the string out of a soon-to-die
 *     TextHolder.
 *   - `TextHolder{ "Hello world!" }.getText()` matches the `&&` overload because
 *     the object expression is a temporary. `textHolder.getText()` matches `&`.
 *   - You can also ref-qualify operators. `operator=(...) &` makes the
 *     "assigning to a temporary" anti-pattern `makeTextHolder() = "Pointless!";`
 *     refuse to compile.
 *   - If you ref-qualify any overload, you must ref-qualify all overloads with
 *     the same name and parameter list.
 *
 * Example:
 *     // Lvalue version returns a reference; rvalue version returns an rvalue ref:
 *     const string& getText() const &  { return m_text; }
 *     string&&      getText() &&       { return move(m_text); }
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
	
	const string& getText() const & { return m_text; }
	string&& getText() && { return move(m_text); }

	TextHolder& operator=(const string& rhs) &
	{
		m_text = rhs;
		return *this;
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
