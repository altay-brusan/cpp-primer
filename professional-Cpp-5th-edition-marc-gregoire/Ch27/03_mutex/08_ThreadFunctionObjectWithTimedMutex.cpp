/*
 * Chapter 27 - Timed Locking with std::timed_mutex and unique_lock
 *
 * A std::timed_mutex lets a thread give up if it cannot acquire the lock within a
 * deadline. Here a unique_lock is constructed with a 200ms relative timeout; its bool
 * conversion (checked via if (lock)) reports whether the lock was obtained. If it was,
 * the thread prints; otherwise it skips that iteration instead of blocking indefinitely.
 */

#include <iostream>
#include <chrono> // newest MSVC no longer pulls <chrono> in transitively via <thread>
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
			unique_lock lock{ ms_timedMutex, 200ms };
			if (lock) {
				cout << format("Counter {} has value {}", m_id, i) << endl;
			} else {
				// Lock not acquired in 200ms, skip output.
			}
		}
	}

private:
	int m_id{ 0 };
	int m_numIterations{ 0 };
	inline static timed_mutex ms_timedMutex;
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
