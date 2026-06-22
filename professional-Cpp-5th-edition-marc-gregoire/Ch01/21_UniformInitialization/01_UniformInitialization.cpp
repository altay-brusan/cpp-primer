/*
 * Chapter 1 - Uniform Initialization
 *
 * Before C++11 the syntax for initializing a struct ({...}) differed from the syntax for
 * initializing a class object (function-call style with parentheses). C++11 unified them:
 * the brace form "{ ... }" works for every type - primitives, aggregates, classes,
 * Standard Library containers, member arrays, dynamically allocated arrays. Prefer it.
 *
 * Key notes:
 *   - "int x { 3 };" and "int x = { 3 };" both perform uniform initialization. The leading
 *     "=" is optional.
 *   - Empty braces zero-initialize: "int n {};" gives 0, "double d {};" gives 0.0,
 *     "T* p {};" gives nullptr. For class types, the default constructor is called.
 *   - Braces reject narrowing conversions at compile time. "int x { 3.14 };" fails to
 *     compile (3.14 cannot be exactly represented as int), while "int x = 3.14;" silently
 *     truncates.
 *   - The "most vexing parse" trap of "T t();" - which declares a function, not a variable -
 *     is avoided by using braces: "T t {};".
 *   - For a single value, beware that "std::vector<int> v(10, 0);" makes a 10-element vector
 *     filled with 0, while "std::vector<int> v { 10, 0 };" makes a 2-element vector { 10, 0 }.
 *     This is the one place where braces behave differently because of initializer_list
 *     constructors.
 */

#include <vector>
#include <string>

using namespace std;

struct CircleStruct
{
	int x, y;
	double radius;
};



class CircleClass
{
public:
	CircleClass(int x, int y, double radius)
		: m_x{ x }, m_y{ y }, m_radius{ radius } {}
private:
	int m_x, m_y;
	double m_radius;
};



void func(int i) { /* ... */ }



class MyClass
{
public:
	MyClass() : m_array{0, 1, 2, 3} {}
private:
	int m_array[4];
};



struct Employee {
	char firstInitial;
	char lastInitial;
	int  employeeNumber;
	int  salary;
};



int main()
{
	// Old pre-C++11 way
	CircleStruct myCircle1 = {10, 10, 2.5};
	CircleClass myCircle2(10, 10, 2.5);

	// C++11 uniform initialization
	CircleStruct myCircle3 = {10, 10, 2.5};
	CircleClass myCircle4 = {10, 10, 2.5};
	CircleStruct myCircle5{10, 10, 2.5};
	CircleClass myCircle6{10, 10, 2.5};

	// Initializing a struct
	Employee anEmployee;
	anEmployee.firstInitial = 'J';
	anEmployee.lastInitial = 'D';
	anEmployee.employeeNumber = 42;
	anEmployee.salary = 80'000;

	// Initializing a struct with uniform initialization
	Employee anEmployee2{ 'J', 'D', 42, 80'000 };

	int a = 3;
	int b(3);
	int c = { 3 }; // Uniform initialization
	int d{ 3 };    // Uniform initialization

	int e{};       // Uniform initialization, e will be 0

	Employee anEmployee3;
	Employee anEmployee4{ };

	// Narrowing
	int x = 3.14;
	func(3.14);

	// Preventing narrowing
	//int x{3.14};       // Error because narrowing
	//func({3.14});      // Error because narrowing

	// Create a MyClass object
	MyClass myClass;

	// Uniform initialization also works with vectors
	vector<string> myVec{"String 1", "String 2", "String 3"};
}
