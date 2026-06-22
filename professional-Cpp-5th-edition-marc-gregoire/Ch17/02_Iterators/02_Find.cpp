/*
 * Chapter 17 - Writing a Generic Algorithm over a Range (myFind)
 *
 * A myFind() function template that scans a [begin, end) range for a value and
 * returns the iterator to the first match, or the end iterator if not found. The
 * value parameter's type is obtained via iterator_traits<Iter>::value_type so the
 * function works for any element type the iterator refers to. The Iter parameter is
 * constrained with the input_iterator concept. std::distance() converts the found
 * iterator back into a positional index.
 */

#include <print>
#include <vector>
#include <iterator>

using namespace std;

template<input_iterator Iter>
auto myFind(Iter begin, Iter end, const typename iterator_traits<Iter>::value_type& value)
{
	for (auto iter{ begin }; iter != end; ++iter) {
		if (*iter == value) {
			return iter;
		}
	}
	return end;
}

int main()
{
	vector values{ 11, 22, 33, 44 };

	auto result{ myFind(cbegin(values), cend(values), 22) };
	if (result != cend(values)) {
		println("Found value at position {}", distance(cbegin(values), result));
	}
}