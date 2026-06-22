/*
 * Chapter 27 - Synchronizing Output with a Mutex and lock_guard
 *
 * To keep two threads' output from interleaving, the Counter class guards each write to
 * cout with a shared static mutex via an RAII std::lock_guard. The lock_guard acquires
 * the mutex on construction and releases it automatically at the end of the loop body,
 * so only one thread prints at a time.
 *
 * Key notes:
 *   - Always acquire mutexes through RAII lock classes rather than calling lock()
 *     and unlock() by hand.
 */

#include <iostream>
#include <format>
#include <mutex>
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
			lock_guard lock{ ms_mutex };
			cout << format("Counter {} has value {}", m_id, i) << endl;
		}
	}

private:
	int m_id{ 0 };
	int m_numIterations{ 0 };
	inline static mutex ms_mutex;
};

int main()
{
	// Using uniform initialization syntax
	jthread t1{ Counter{ 1, 20 } };

	// Using named variable
	Counter c{ 2, 12 };
	jthread t2{ c };

	// No need to manually call join(), as we are using jthread.
}

