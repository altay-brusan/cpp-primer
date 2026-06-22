/*
 * Chapter 19 - std::move_only_function
 *
 * Demonstrates std::move_only_function (C++23), a wrapper like std::function but able to
 * store callables that are move-only. BigDataProcessor owns a unique_ptr<BigData> and so
 * cannot be copied; it is moved into a move_only_function<void() const> and then invoked.
 * The const in the template signature requires the stored callable's call operator to be
 * const-callable.
 */
#include <print>
#include <memory>
#include <utility>
#include <functional>

using namespace std;

class BigData {};

class BigDataProcessor
{
public:
	explicit BigDataProcessor(unique_ptr<BigData> data) : m_data{ move(data) } {}
	void operator()() const { println("Processing BigData instance..."); }
private:
	unique_ptr<BigData> m_data;
};

int main()
{
	auto data{ make_unique<BigData>() };
	const move_only_function<void() const> processor{ BigDataProcessor{ move(data) } };
	processor();
}
