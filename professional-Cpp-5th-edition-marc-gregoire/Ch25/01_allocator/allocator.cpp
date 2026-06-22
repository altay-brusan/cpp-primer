/*
 * Chapter 25 - Using std::allocator Directly
 *
 * Every Standard Library container takes an Allocator template parameter (defaulting to
 * std::allocator) that controls how it obtains and releases raw memory. This contrived sample
 * uses an allocator by hand to separate the two halves of object lifetime: allocate() reserves
 * an uninitialized block (a wrapper around operator new) without constructing anything, and a
 * placement new expression then constructs a MyClass in that block. Tear-down mirrors this:
 * std::destroy_at runs the destructor, then deallocate() returns the raw memory.
 *
 * Key notes:
 *   - allocate() and deallocate() only manage memory; they never call constructors or destructors.
 *   - Writing a fully custom Allocator (or using std::pmr polymorphic allocators) is an advanced,
 *     rarely needed task; this sample only exercises the default allocator's interface.
 */

#include <memory>

class MyClass {};

int main()
{
	// Create an allocator to use.
	std::allocator<MyClass> alloc;

	// Allocate an uninitialized memory block for 1 instance of MyClass.
	auto* memory{ alloc.allocate(1) };

	// Use placement new operator to construct a MyClass in place.
	::new(memory) MyClass{};

	// Destroy MyClass instance.
	std::destroy_at(memory);

	// Deallocate memory block.
	alloc.deallocate(memory, 1);
	memory = nullptr;
}
