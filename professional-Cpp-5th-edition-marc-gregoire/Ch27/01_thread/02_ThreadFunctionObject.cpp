/*
 * Chapter 27 - Launching a Thread with a Function Object
 *
 * Instead of a function pointer, a thread can execute the operator() of a function
 * object. The advantage over a plain function is that state (here the id and iteration
 * count) lives in data members initialized through the constructor. Shows two ways to
 * give the thread a Counter: an inline temporary via uniform initialization, and a
 * named variable.
 *
 * Key notes:
 *   - The function object is copied into internal storage for the thread; use
 *     std::ref() or cref() if you need operator() to run on your original instance.
 */

#include <print>
#include <thread>

using namespace std;

class Counter
{
public:
	explicit Counter(int id, int numIterations)
		: m_id{ id }, m_numIterations{ numIterations }
	{
	}

	void operator()() const
	{
		for (int i{ 0 }; i < m_numIterations; ++i) {
			println("Counter {} has value {}", m_id, i);
		}
	}

private:
	int m_id{ 0 };
	int m_numIterations{ 0 };
};

int main()
{
	// Using uniform initialization syntax.
	thread t1{ Counter{ 1, 20 } };

	// Using named variable.
	Counter c{ 2, 12 };
	thread t2{ c };

	// Wait for threads to finish.
	t1.join();
	t2.join();
}
