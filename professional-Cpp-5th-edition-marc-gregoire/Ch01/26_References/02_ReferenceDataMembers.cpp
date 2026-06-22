/*
 * Chapter 1 - Reference Data Members
 *
 * A reference must be initialized the moment it comes into existence. For a reference data
 * member that means initializing it in the constructor's initializer list, never by
 * assignment in the constructor body.
 *
 * Key notes:
 *   - Syntax: "ClassName(int& ref) : m_ref { ref } { ... }". Place the colon after the
 *     parameter list and list each member as "name { expr }".
 *   - A class with a reference data member cannot be default-constructed and cannot be copy-
 *     assigned (the reference can never be rebound). It can still be copy-constructed.
 *   - The referent must outlive the object. Storing a reference to a temporary or to a local
 *     in another function is a dangling-reference bug.
 *   - Reference members work well for "this object observes that one"; for ownership prefer
 *     a smart pointer (e.g. std::unique_ptr).
 */

class MyClass
{
public:
	MyClass(int& ref) : m_ref{ ref } { /* Body of constructor */ }

private:
	int& m_ref;
};

int main()
{
	int i{ 123 };
	MyClass m{ i };
}
