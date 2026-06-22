/*
 * Chapter 10 - Changing Access in a Derived Class (1/4): Tightening access
 *
 * Shy inherits a public `talk()` from Gregarious and overrides it as
 * `protected`. The override is still callable - but only through a base
 * reference where the *static* type still says "public talk()".
 *
 *   - `myShy.talk()`         -> Error: access is checked on the static type Shy.
 *   - `Gregarious& ref{...}; ref.talk();` -> OK: static type Gregarious has it public.
 *
 * Key notes:
 *   - Access is checked at the call site against the static type. The
 *     override's access modifier matters when you call through Derived.
 *   - This is sometimes used to expose a function to subclasses only while
 *     keeping the public surface intact through a base reference.
 *   - The next three samples explore the inverse direction (broadening
 *     access) and the using-declaration shortcut.
 */
#include <print>

using namespace std;

class Gregarious
{
public:
	virtual ~Gregarious() = default;
	virtual void talk() { println("Gregarious says hi!"); }
};

class Shy : public Gregarious
{
protected:
	void talk() override { println("Shy reluctantly says hello."); }
};

int main()
{
	{
		Shy myShy;
		//myShy.talk();   // Error: protected when seen as Shy.
	}

	{
		Shy myShy;
		Gregarious& ref{ myShy };
		ref.talk();       // OK: public when seen as Gregarious. Virtual dispatch picks Shy's body.
	}
}
