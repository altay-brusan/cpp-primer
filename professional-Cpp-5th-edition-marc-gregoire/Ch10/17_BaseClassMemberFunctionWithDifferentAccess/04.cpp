/*
 * Chapter 10 - Changing Access (4/4): Republish with a using-declaration
 *
 * `using Secret::dontTell;` placed in Blabber's public section re-exposes the
 * inherited (still-protected-in-Secret) function as public on Blabber - WITHOUT
 * overriding the body. Calls through Blabber are public; calls through a
 * `Secret&` or `Secret*` still see it as protected.
 *
 * Key notes:
 *   - This is the minimal way to "publish" a base feature on a subclass when
 *     you don't want to change behavior, just change visibility.
 *   - Access is part of the *declaration in the deriving class*, not a global
 *     property of the function. The base's view of the function is unchanged
 *     - hence the two commented errors at the bottom of main().
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
	using Secret::dontTell;     // republish at public access; body unchanged
};

int main()
{
	Blabber myBlabber;
	myBlabber.dontTell();   // OK - public through Blabber. Outputs "I'll never tell."

	Secret& ref{ myBlabber };
	Secret* ptr{ &myBlabber };
	//ref.dontTell();       // Error - still protected when seen as Secret.
	//ptr->dontTell();      // Error - same.
}
