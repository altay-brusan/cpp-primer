/*
 * Chapter 10 - Changing Access (3/4): Override with a wider access modifier
 *
 * Same setup as 02.cpp, but Blabber promotes the base's protected `dontTell`
 * to *public* by overriding it in the public section. Now external code can
 * call `myBlabber.dontTell()` directly, and the override gives it a different
 * body too.
 *
 * Key notes:
 *   - You're allowed to change access in either direction in a derived class.
 *     Widening is sometimes legitimate (you're publishing a new policy);
 *     narrowing is rare and usually a smell.
 *   - This also overrides the body, so the protected base implementation
 *     never runs. If you only wanted to expose it without changing behavior,
 *     04.cpp shows the simpler `using` form.
 */
#include <print>

using namespace std;

class Secret
{
protected:
	virtual void dontTell() { println("I'll never tell."); }
};

class Blabber : public Secret
{
public:
	void dontTell() override { println("I'll tell all!"); }   // promoted to public
};

int main()
{
	Blabber myBlabber;
	myBlabber.dontTell();   // Outputs "I'll tell all!"
}
