/*
 * Chapter 19 - priority_queue with greater Comparator
 *
 * Same priority_queue example, but with the comparison function object changed to the
 * transparent greater<>. Because Compare is the last template parameter, the container
 * type (vector<int>) must also be spelled out to supply it. With greater, the smallest
 * element becomes the top, so values come out in ascending order (1 2 3 4).
 *
 * Key notes:
 *   - Prefer transparent comparators (greater<>) for containers that take a comparator.
 */
#include <print>
#include <queue>
#include <vector>
#include <functional>

using namespace std;

int main()
{
	priority_queue<int, vector<int>, greater<>> myQueue;

	myQueue.push(3);
	myQueue.push(4);
	myQueue.push(2);
	myQueue.push(1);

	while (!myQueue.empty()) {
		print("{} ", myQueue.top());
		myQueue.pop();
	}
}
