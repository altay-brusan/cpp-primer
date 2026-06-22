/*
 * Chapter 26 - Writing Your Own Type Trait with Partial Specialization
 *
 * Reimplements std::remove_pointer to show how transformation traits are built.
 * The primary my_remove_pointer<T> exposes type = T, while partial
 * specializations for T* and T* const strip the pointer, exposing type = T. An
 * accompanying my_remove_pointer_t alias template provides the convenient form.
 */

#include <print>
#include <type_traits>

using namespace std;

// my_remove_pointer class template.
template <typename T>
struct my_remove_pointer {
	using type = T;
};

// Partial specialization for pointer types.
template <typename T>
struct my_remove_pointer<T*> {
	using type = T;
};

// Partial specialization for const pointer types.
template <typename T>
struct my_remove_pointer<T* const> {
	using type = T;
};

// Alias template for ease of use.
template <typename T>
using my_remove_pointer_t = typename my_remove_pointer<T>::type;

int main()
{
	println("{}", is_same_v<string, my_remove_pointer_t<string*>>);
}