/*
 * Chapter 14 - Test Driver for Constructor Error Handling
 *
 * Exercises the Matrix<T> class template - see Matrix.h for the conceptual notes
 * on throwing from and cleaning up after a failing constructor. main() simply
 * constructs a Matrix<Element> of size 10x10; with the trivial Element this
 * succeeds, but the machinery would correctly clean up if any element
 * constructor threw.
 */

#include "Element.h"
#include "Matrix.h"

int main()
{
	Matrix<Element> m{ 10, 10 };
}
