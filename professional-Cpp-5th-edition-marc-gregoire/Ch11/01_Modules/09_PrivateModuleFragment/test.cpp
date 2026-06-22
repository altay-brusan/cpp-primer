/*
 * Chapter 11 - Modules (9/10): Driver
 *
 * `getImplementation()` returns a pointer, but the type is incomplete on
 * the client side - so calls on it don't compile. That's the encapsulation
 * payoff of the private module fragment.
 */
import std;
import adder;

using namespace std;

int main()
{
	Adder adder;
	println("Value: {}", adder.add(20, 22));
	auto impl{ adder.getImplementation() };
	//auto result{ impl->add(20, 22) }; // Error! Impl is incomplete here.
}
