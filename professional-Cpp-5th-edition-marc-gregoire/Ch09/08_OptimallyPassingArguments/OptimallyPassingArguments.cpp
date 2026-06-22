/*
 * Chapter 9 - Optimal Way to Pass Arguments to Functions
 *
 * When a function's job is to copy its argument into a member, three pass styles all
 * achieve the goal:
 *   1) `void setData(const vector<int>& data) { m_data = data; }` - one copy on
 *      assignment whether the caller passes an lvalue or an rvalue.
 *   2) Overload pair: const-ref for lvalues plus `vector<int>&&` for rvalues - two
 *      functions to maintain.
 *   3) Pass-by-value: `void setData(vector<int> data) { m_data = std::move(data); }`
 *      - one function, optimal for both lvalues (one copy in, then move) and
 *      rvalues (move in, move on).
 *
 * Key notes:
 *   - Choose pass-by-value only when the function would have copied the argument
 *     anyway AND the type supports move semantics. Otherwise stick with const-ref.
 *   - Do not use pass-by-value for "look but do not touch" arguments; an
 *     unnecessary copy is still a cost.
 *   - The inner `std::move(data)` is the move that turns the parameter (an lvalue
 *     name) back into an rvalue so `m_data` can absorb its guts.
 *   - Rvalues passed in are MOVED into `data`, not copied - this is the whole point.
 *
 * Example:
 *     // The same setData() handles both:
 *     wrapper.setData(myData);              // lvalue: copy into data, move into m_data
 *     wrapper.setData({ 22, 33, 44 });      // rvalue: move into data, move into m_data
 */
#include <vector>
#include <utility>

using namespace std;

class DataHolder
{
public:
	//void setData(const vector<int>& data) { m_data = data; }
	//void setData(vector<int>&& data) { m_data = move(data); }
	void setData(vector<int> data) { m_data = move(data); }

private:
	vector<int> m_data;
};

int main()
{
	DataHolder wrapper;
	vector myData{ 11, 22, 33 };
	wrapper.setData(myData);

	wrapper.setData({ 22, 33, 44 });
}
