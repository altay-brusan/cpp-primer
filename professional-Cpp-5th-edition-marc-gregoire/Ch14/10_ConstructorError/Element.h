/*
 * Chapter 14 - Element Type for the Constructor-Error Matrix
 *
 * A minimal element type used to instantiate Matrix<T> in ConstructorErrorTest.
 * Kept trivial here, but as the comment notes, in practice such a class could
 * throw exceptions from its own constructor - which is exactly the situation the
 * Matrix constructor's cleanup logic is designed to survive.
 */

#pragma	once

class Element
{
	// Kept to a bare minimum, but in practice, this Element class
	// could throw exceptions in its constructor.
private:
	int m_value;
};
