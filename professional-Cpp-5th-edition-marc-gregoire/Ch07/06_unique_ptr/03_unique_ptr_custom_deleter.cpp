/*
 * Chapter 7 - unique_ptr / Custom Deleters
 *
 * By default `unique_ptr` calls `delete` on its raw pointer. You can swap in any
 * function (or callable) to run instead - useful for resources whose teardown is not
 * `delete`: closing a `FILE*`, freeing a C API handle, returning a slot to a pool, etc.
 * The catch is the syntax: the deleter's type becomes part of the `unique_ptr`'s type,
 * which is why you see `decltype(&my_free)` as the second template argument.
 *
 * Key notes:
 *   - The deleter type clutters the `unique_ptr` declaration and is awkward to pass
 *     around - `shared_ptr` accepts a deleter as a constructor argument with no template
 *     parameter, which is much cleaner (see folder 07).
 *   - The deleter must be passed at construction time; it cannot be defaulted.
 *   - A stateless lambda or function pointer makes a fine deleter; for stateful
 *     deleters consider a callable object.
 *   - This trick lets `unique_ptr` manage any RAII resource, not just heap memory.
 */

#include <memory>

using namespace std;

int* my_alloc(int value)
{
	return new int{ value };
}

void my_free(int* p)
{
	delete p;
}

int main()
{
	// Template args: <T, DeleterType>. decltype(&my_free) yields `void(*)(int*)`.
	// Constructor args: <raw pointer, deleter value>.
	unique_ptr<int, decltype(&my_free)> myIntSmartPtr{ my_alloc(42), my_free };
}
