/*
 * Chapter 27 - Avoiding Interleaved Output with std::osyncstream
 *
 * Writing to cout from several threads is thread-safe but the lines can still interleave.
 * std::osyncstream (from <syncstream>) buffers everything written to it and atomically
 * flushes it to the underlying stream when the osyncstream is destroyed, so each line
 * appears intact. Two Counter function objects run on jthreads, each using a per-line
 * osyncstream wrapping cout.
 */

#include <iostream>
#include <syncstream>
#include <format>
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
			osyncstream syncedCout{ cout };
			syncedCout << format("Counter {} has value {}", m_id, i);
			syncedCout << endl;
			// Upon destruction, syncedCout atomically flushes
			// its contents into cout.
		}
	}

private:
	int m_id{ 0 };
	int m_numIterations{ 0 };
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

