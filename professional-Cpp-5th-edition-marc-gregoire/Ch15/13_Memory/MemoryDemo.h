/*
 * Chapter 15 - Overloading the Memory Allocation and Deallocation Operators
 *
 * Declares a class that overloads operator new and operator delete (plus the array and
 * nothrow forms, and a custom form taking an extra int parameter). Overloading these lets
 * a class control how memory is allocated and freed for its instances, independent of the
 * new-expression/delete-expression that still invoke the constructor and destructor.
 *
 * Key notes:
 *   - Always overload the matching operator delete for every operator new you provide.
 *   - The extra-parameter operator new (size, int) corresponds to a new(5) MemoryDemo{}
 *     placement-style call; its operator delete only runs if the constructor throws.
 *   - A commented-out operator delete taking a size_t shows the size-aware deallocation
 *     form mentioned in the chapter.
 */
#pragma once

#include <new>
#include <cstddef>

class MemoryDemo
{
public:
	virtual ~MemoryDemo() = default;

	void* operator new(std::size_t size);
	void operator delete(void* ptr) noexcept;
	//void operator delete(void* ptr, std::size_t size) noexcept;

	void* operator new[](std::size_t size);
	void operator delete[](void* ptr) noexcept;
	
	void* operator new(std::size_t size, const std::nothrow_t&) noexcept;
	void operator delete(void* ptr, const std::nothrow_t&) noexcept;

	void* operator new[](std::size_t size, const std::nothrow_t&) noexcept;
	void operator delete[](void* ptr, const std::nothrow_t&) noexcept;


	void* operator new(std::size_t size, int extra);
	void operator delete(void* ptr, int extra) noexcept;
};
