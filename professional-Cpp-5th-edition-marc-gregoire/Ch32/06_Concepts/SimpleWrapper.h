/*
 * Chapter 32 - Constraining Template Parameters with Concepts (syntax refresher)
 *
 * The same SimpleWrapper class template as the previous sample, but now its type parameter
 * T is constrained with a requires clause to be either a floating-point or an integral
 * type. Instantiating it with any other type (for example std::string) is a compilation
 * error, which the driver demonstrates in commented-out code.
 *
 * Key notes:
 *   - Concepts (C++20) express requirements on template parameters and produce clearer
 *     diagnostics than raw template substitution failures.
 */
#pragma once

#include <concepts>

template <typename T> requires (std::floating_point<T> || std::integral<T>)
class SimpleWrapper
{
public:
	explicit SimpleWrapper(T& object) : m_object{ object } { }
	T& get() const { return m_object; }

private:
	T& m_object;
};
