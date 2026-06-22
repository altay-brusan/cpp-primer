/*
 * Chapter 14 - Handling Errors in Constructors
 *
 * A Matrix<T> class template that allocates a 2D array of raw pointers and shows
 * how a constructor handles exceptions. Constructors have no return value, so
 * they signal failure by throwing - but if an exception leaves a constructor,
 * the object's destructor is NEVER called, so the constructor must free anything
 * it already allocated itself. The ctor zero-initializes the outer array with {}
 * so cleanup() can safely delete[] partially-filled rows, wraps the inner
 * allocations in try/catch (...), calls cleanup(), and nests the caught
 * exception inside a std::bad_alloc via throw_with_nested().
 *
 * Key notes:
 *   - m_width/m_height are assigned only after the first allocation succeeds, so
 *     cleanup() never iterates over memory that was not allocated.
 *   - Raw pointers are used to illustrate the problem; real code should use a
 *     Standard Library container or smart pointer instead.
 */

#pragma	once

#include <print>
#include <iostream>
#include <cstddef>
#include <new>

template <typename T>
class Matrix final
{
public:
	explicit Matrix(std::size_t width, std::size_t height);
	~Matrix();
	Matrix(const Matrix&) = delete;
	Matrix(Matrix&&) = delete;
	Matrix& operator=(const Matrix&) = delete;
	Matrix& operator=(Matrix&&) = delete;

private:
	void cleanup();

	std::size_t m_width{ 0 };
	std::size_t m_height{ 0 };
	T** m_matrix{ nullptr };
};

template <typename T>
Matrix<T>::Matrix(std::size_t width, std::size_t height)
{
	m_matrix = new T*[width] {};	// Array is zero-initialized!

	// Don't initialize the m_width and m_height members in the ctor-
	// initializer. These should only be initialized when the above
	// m_matrix allocation succeeds!
	m_width = width;
	m_height = height;

	try {
		for (std::size_t i{ 0 }; i < width; ++i) {
			m_matrix[i] = new T[height];
		}
	} catch (...) {
		std::println(std::cerr, "Exception caught in constructor, cleaning up...");
		cleanup();
		// Nest any caught exception inside a bad_alloc exception.
		std::throw_with_nested(std::bad_alloc{});
	}
}

template <typename T>
Matrix<T>::~Matrix()
{
	cleanup();
}

template <typename T>
void Matrix<T>::cleanup()
{
	for (std::size_t i{ 0 }; i < m_width; ++i) {
		delete[] m_matrix[i];
	}
	delete[] m_matrix;
	m_matrix = nullptr;
	m_width = m_height = 0;
}
