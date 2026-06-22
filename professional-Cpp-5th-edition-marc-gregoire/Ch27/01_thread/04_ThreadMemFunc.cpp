/*
 * Chapter 27 - Launching a Thread with a Member Function
 *
 * A thread can run a member function on a specific object. You pass a pointer to the
 * member function (&Request::process) followed by a pointer to the instance it should
 * run on (&req). This executes that method on that object in a separate thread.
 *
 * Key notes:
 *   - If other threads also touch the same object, you must synchronize access (for
 *     example with a mutex) to avoid data races.
 */

#include <print>
#include <thread>

using namespace std;

class Request
{
public:
	explicit Request(int id) : m_id{ id } { }

	void process()
	{
		println("Processing request {}", m_id);
	}

private:
	int m_id{ 0 };
};

int main()
{
	Request req{ 100 };
	thread t{ &Request::process, &req };

	t.join();
}
