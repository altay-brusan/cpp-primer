/*
 * Chapter 13 - Output with Objects: a Custom std::formatter (the Solution)
 *
 * The modern answer to the previous sample's problem: specialize
 * std::formatter<Muffin> so a Muffin can be passed straight to println()/format
 * with the "{}" placeholder, just like a built-in type. The minimal formatter
 * implements parse() and format(), the latter writing the muffin's fields via
 * format_to() and advancing the output context.
 */

#include <print>
#include <string>
#include <format>
#include <utility>

using namespace std;

class Muffin final
{
public:
	const string& getDescription() const { return m_description; }
	void setDescription(string description) { m_description = std::move(description); }

	int getSize() const { return m_size; }
	void setSize(int size) { m_size = size; }

	bool hasChocolateChips() const { return m_hasChocolateChips; }
	void setHasChocolateChips(bool hasChips) { m_hasChocolateChips = hasChips; }

private:
	string m_description;
	int m_size{ 0 };
	bool m_hasChocolateChips{ false };
};

template <>
class std::formatter<Muffin>
{
public:
	constexpr auto parse(auto& context)
	{
		return begin(context);
	}

	auto format(const Muffin& muffin, auto& ctx) const
	{
		ctx.advance_to(format_to(ctx.out(), "{}, size is {}, {}",
			muffin.getDescription(), muffin.getSize(),
			(muffin.hasChocolateChips() ? "has chips" : "no chips")));
		return ctx.out();
	}
};


int main()
{
	println("Let's create a muffin in code and print it.");

	Muffin myMuffin;
	myMuffin.setDescription("Giant Blueberry Muffin");
	myMuffin.setSize(42);
	myMuffin.setHasChocolateChips(false);

	println("The muffin is a {} -- yummy!", myMuffin);
}
