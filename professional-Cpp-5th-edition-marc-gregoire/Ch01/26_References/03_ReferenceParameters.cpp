/*
 * Chapter 1 - Reference Parameters
 *
 * The default parameter-passing mode is by value - the function works on a copy and any
 * modification dies when the function returns. Declaring the parameter as "T&" switches to
 * pass-by-reference: the function operates directly on the caller's variable.
 *
 * Key notes:
 *   - Non-const reference parameters cannot bind to literals or temporaries. "swap(3, 4)"
 *     fails to compile because 3 and 4 have no address to refer to.
 *   - At the call site, the syntax is identical to pass-by-value: "swap(x, y);" - no &
 *     decorating the arguments. Easy to miss that x and y may be modified.
 *   - To pass an object indicated by a pointer into a reference parameter, dereference it:
 *     "swap(*xp, *yp);". The reference will refer to the same object the pointer points to.
 *   - For large objects you do NOT need to modify, prefer "const T&" (next sample) - same
 *     no-copy efficiency, with the safety of read-only access.
 */

void addOneA(int i)
{
	i++;  // Has no real effect because this is a copy of the original
}

void addOneB(int& i)
{
	i++;  // Actually changes the original variable
}

void swap(int& first, int& second)
{
	int temp{ first };
	first = second;
	second = temp;
}

int main()
{
	int myInt{ 7 };
	addOneA(myInt);
	addOneB(myInt);



	int x{ 5 }, y{ 6 };
	swap(x, y);

	//  swap(3, 4); // DOES NOT COMPILE

	int* xp{ &x }, * yp{ &y };
	swap(*xp, *yp);
}
