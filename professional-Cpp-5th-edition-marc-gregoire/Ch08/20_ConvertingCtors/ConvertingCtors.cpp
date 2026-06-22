/*
 * Chapter 8 - Converting Constructors (multi-argument and explicit)
 *
 * Since C++11, any constructor - even one taking multiple arguments - can be a converting
 * constructor through brace-elision. That means `process({1, 2})` would happily build a
 * temporary `MyClass{1, 2}` and pass it to `process`. Marking the constructors `explicit`
 * forbids those implicit conversions; callers have to spell `MyClass{...}` themselves.
 *
 * Key notes:
 *   - Pre-C++11 only single-arg constructors were "converting"; since C++11, multi-arg
 *     ones can also be converted from brace lists.
 *   - `explicit` works on any constructor, regardless of arity.
 *   - C++20 adds conditional `explicit(bool)`, useful in generic code where you only want
 *     to be explicit for some template instantiations.
 *   - The commented-out calls would each fail to compile against this `explicit` class -
 *     that is the demonstration.
 *
 * Example:
 *     // C++20 conditional explicit:
 *     explicit(SomeTypeTrait<T>::value) MyClass(T);
 */

class MyClass
{
public:
	explicit MyClass(int) { }
	explicit MyClass(int, int) { }
};


void process(const MyClass& c) { }

int main()
{
	//process(1);
	//process({ 1 });
	//process({ 1, 2 });

	process(MyClass{ 1 });
	process(MyClass{ 1, 2 });
}
