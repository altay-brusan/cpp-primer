/*
 * Chapter 12 - Class Template Argument Deduction (CTAD) and Deduction Guides
 *
 * Since C++17 you can sometimes drop the template argument when
 * constructing a class template - the compiler deduces it from the ctor
 * arguments. Here `SpreadsheetCell cell{myString};` deduces to
 * `SpreadsheetCell<std::string>` because `myString` is a `std::string`.
 *
 * But `SpreadsheetCell cell2{"test"};` is tricky: `"test"` is a
 * `const char*`, so the compiler would deduce `SpreadsheetCell<const char*>`,
 * which is probably not what we want.
 *
 * The fix: a *deduction guide*.
 *
 *   SpreadsheetCell(const char*) -> SpreadsheetCell<std::string>;
 *
 * This tells the compiler: "when a ctor argument is `const char*`,
 * actually deduce `SpreadsheetCell<std::string>` instead". Now `cell2` is
 * a `SpreadsheetCell<std::string>` like you'd expect.
 *
 * Key notes:
 *   - Deduction guides live OUTSIDE the class definition, in the same
 *     namespace.
 *   - The arrow syntax mirrors trailing return types - that's intentional.
 *   - Many Standard Library types ship guides for this exact reason
 *     (e.g. `std::vector v{1,2,3}` deduces vector<int>).
 *   - If a guide is `explicit`, it only applies to direct-initialization,
 *     not to copy-initialization. Most guides don't bother.
 */
#include <string>
#include <utility>

using namespace std;

template <typename T>
class SpreadsheetCell
{
public:
	explicit SpreadsheetCell(T t) : m_content{ move(t) } { }
	const T& getContent() const { return m_content; }
private:
	T m_content;
};

SpreadsheetCell(const char*) -> SpreadsheetCell<std::string>;

int main()
{
	string myString{ "Hello World!" };
	SpreadsheetCell cell{ myString };

	SpreadsheetCell cell2{ "test" };
}
