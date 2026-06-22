/*
 * Chapter 19 - priority_queue with Default less Comparator
 *
 * Shows a std::priority_queue<int> using its default comparison function object,
 * std::less. Because the largest element compares "greatest," top() yields values in
 * descending order (4 3 2 1). This sets up the contrast with the greater comparator in
 * the next sample.
 */
#include <print>
#include <queue>

using namespace std;

int main()
{
	priority_queue<int> myQueue;

	myQueue.push(3);
	myQueue.push(4);
	myQueue.push(2);
	myQueue.push(1);

	while (!myQueue.empty()) {
		print("{} ", myQueue.top());
		myQueue.pop();
	}
}
