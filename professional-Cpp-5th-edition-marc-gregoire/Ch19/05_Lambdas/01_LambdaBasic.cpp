/*
 * Chapter 19 - Lambda Expression Syntax Basics
 *
 * A guided tour of lambda syntax built up step by step: a stateless lambda with an empty
 * capture block, a lambda taking a parameter, a lambda with an explicit trailing return
 * type (-> int) and one with the return type omitted for deduction. It then shows return
 * type deduction stripping const and reference (a copy of the name is returned) versus
 * using decltype(auto) to preserve const string&. Finally it covers captures: by value
 * [data], a mutable by-value lambda that modifies its own copy, and by reference [&data]
 * which changes the variable in the enclosing scope.
 *
 * Key notes:
 *   - A by-value capture is read-only unless the lambda is declared mutable.
 *   - mutable requires the parameter parentheses even when empty.
 */
#include <print>
#include <string>
#include <utility>

using namespace std;

class Person
{
public:
	explicit Person(std::string name) : m_name{ std::move(name) } { }
	const std::string& getName() const { return m_name; }

private:
	std::string m_name;
};

int main()
{
	// Basic lambda
	auto basicLambda{ [] { println("Hello from Lambda"); } };
	basicLambda();

	// Lambda with parameters
	auto parametersLambda{ [](int value) { println("The value is {}", value); } };
	parametersLambda(42);

	// Lambda returning a value
	auto sumLambda{ [](int a, int b) -> int { return a + b; } };
	int sum{ sumLambda(11, 22) };
	println("The result is {}", sum);

	// Lambda returning a value, with return type omitted
	auto sumLambda2{ [](int a, int b) { return a + b; } };
	sum = sumLambda2(11, 22);
	println("The result is {}", sum);

	// Demonstrating stripping of reference and const qualifiers
	Person p{ "John Doe" };
	decltype(auto) name1{ [](const Person& person) { return person.getName(); }(p) };
	decltype(auto) name2{ [](const Person& person) -> decltype(auto) { return person.getName(); }(p) };

	// Lambda capturing a variable by value
	double data{ 1.23 };
	auto capturingVLambda{ [data] { println("Data = {}", data); } };
	capturingVLambda();

	// Lambda capturing a variable by value
	auto capturingVLambda2{ [data]() mutable { data *= 2; println("Data = {}", data); } };
	capturingVLambda2();

	// Lambda capturing a variable by reference
	auto capturingRLambda{ [&data] { data *= 2; } };
	capturingRLambda();
	println("Data = {}", data);
}
