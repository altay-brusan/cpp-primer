/*
 * Chapter 15 - Overloading the Dereferencing Operators (* and ->)
 *
 * A minimal smart-pointer class template that owns a raw pointer and overloads the
 * dereferencing operators so objects behave like pointers. operator* returns a reference
 * to the pointee (T&), while operator-> returns the raw pointer (T*); C++ then re-applies
 * -> to that result, which is why the two are asymmetric. Both come in const and non-const
 * forms, and copy is deleted while move is allowed so ownership is unique.
 *
 * Key notes:
 *   - Always provide operator* and operator-> together; supplying only one confuses users.
 *   - This is for teaching only - prefer std::unique_ptr / std::shared_ptr in real code.
 */
#pragma once

#include <utility>

template <typename T>
class Pointer
{
public:
	explicit Pointer(T* ptr) : m_ptr{ ptr } { }

	virtual ~Pointer()
	{
		reset();
	}

	// Disallow copy constructor and copy assignment.
	Pointer(const Pointer& src) = delete;
	Pointer& operator=(const Pointer& rhs) = delete;

	// Allow move construction.
	Pointer(Pointer&& src) noexcept : m_ptr{ std::exchange(src.m_ptr, nullptr) }
	{
	}

	// Allow move assignment.
	Pointer& operator=(Pointer&& rhs) noexcept
	{
		if (this != &rhs) {
			reset();
			m_ptr = std::exchange(rhs.m_ptr, nullptr);
		}
		return *this;
	}

	T& operator*() { return *m_ptr; }
	const T& operator*() const { return *m_ptr; }

	T* operator->() { return m_ptr; }
	const T* operator->() const { return m_ptr; }

private:
	void reset()
	{
		delete m_ptr;
		m_ptr = nullptr;
	}
	T* m_ptr{ nullptr };
};
