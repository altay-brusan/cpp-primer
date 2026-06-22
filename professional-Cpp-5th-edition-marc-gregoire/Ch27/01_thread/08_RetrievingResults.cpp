/*
 * Chapter 27 - Retrieving Results from a Thread via a Function Object
 *
 * One way to get a result out of a thread is to store it in data members of a function
 * object and read them after the thread finishes. This works only if the object is
 * passed by reference with std::ref(); otherwise the thread operates on a copy and the
 * caller never sees the result. After join(), main() reads the computed result from the
 * original Calculator instance. (Futures, shown later, are usually the easier option.)
 */

#include <print>
#include <thread>
#include <functional>

using namespace std;

class Calculator
{
public:
	explicit Calculator(int a, int b) : m_a{ a }, m_b{ b } {}
	void operator()() { result = m_a * m_b; }
	int getResult() const { return result; }
private:
	int m_a{ 0 };
	int m_b{ 0 };
	int result{ 0 };
};

int main()
{
	Calculator calculator{ 21, 2 };
	jthread job{ ref(calculator) };
	job.join();
	println("21*2 = {}", calculator.getResult());
}
