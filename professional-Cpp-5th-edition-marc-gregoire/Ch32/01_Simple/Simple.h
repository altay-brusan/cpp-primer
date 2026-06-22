/*
 * Chapter 32 - Writing a Class from Scratch (syntax refresher)
 *
 * A reference template for the syntax of a complete class definition. It shows the
 * three access levels, a defaulted virtual destructor (so the class is safe to derive
 * from), deleted copy operations paired with defaulted move operations, and the various
 * member kinds: virtual member functions, data members with in-class initializers, a
 * private constant, and a static inline data member.
 *
 * Key notes:
 *   - The public and protected data members shown here are for illustration only - real
 *     classes should keep data private and expose getters and setters.
 *   - Deleting the copy constructor and copy assignment operator forbids copying and
 *     pass-by-value; the move operations are explicitly defaulted to keep them usable.
 */
#pragma once

// A simple class that illustrates class definition syntax.
class Simple
{
public:
	Simple();                              // Constructor
	virtual ~Simple() = default;           // Defaulted virtual destructor

	// Disallow copy construction and copy assignment.
	Simple(const Simple& src) = delete;
	Simple& operator=(const Simple& rhs) = delete;

	// Explicitly default move constructor and move assignment operator.
	Simple(Simple&& src) = default;
	Simple& operator=(Simple&& rhs) = default;

	virtual void publicMemberFunction();   // Public member function
	int m_publicInteger;                   // Public data member

protected:
	virtual void protectedMemberFunction();// Protected member function
	int m_protectedInteger{ 41 };          // Protected data member

private:
	virtual void privateMemberFunction();  // Private member function
	int m_privateInteger{ 42 };            // Private data member
	static constexpr int Constant{ 2 };    // Private constant
	static inline int ms_staticInt{ 3 };   // Private static data member
};
