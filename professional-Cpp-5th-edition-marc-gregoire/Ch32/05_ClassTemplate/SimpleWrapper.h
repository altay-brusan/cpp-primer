/*
 * Chapter 32 - Writing a Class Template (syntax refresher)
 *
 * A class template that wraps a reference to an object of any type T and exposes it via
 * get(). Because templates must be visible where they are used, the member functions are
 * defined inline in this header rather than in a separate .cpp file.
 *
 * Key notes:
 *   - This version accepts any T; the next sample (06_Concepts) constrains T with concepts.
 *   - Storing a reference means the wrapper always reflects the current value of the
 *     wrapped object, as the driver demonstrates by mutating it after wrapping.
 */
#pragma once

template <typename T>
class SimpleWrapper
{
public:
	explicit SimpleWrapper(T& object) : m_object{ object } { }
	T& get() const { return m_object; }

private:
	T& m_object;
};
