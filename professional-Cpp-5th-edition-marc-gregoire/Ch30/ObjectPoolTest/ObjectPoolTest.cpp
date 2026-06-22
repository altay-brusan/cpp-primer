/*
 * Chapter 30 - Writing Unit Tests with the Microsoft Visual C++ Testing Framework
 *
 * Implementation of the test methods declared in ObjectPoolTest.h - see the header for the
 * conceptual notes. Each method is a self-contained unit test that uses Assert macros to
 * validate one aspect of the ObjectPool: testSimple is a trivial first test, testException
 * shows Assert::ExpectException for verifying that code throws, and testCreation, testAcquire,
 * testExclusivity, and testRelease check construction, object acquisition, uniqueness of
 * handed-out objects, and correct reuse of released storage. The tests follow the
 * IF-WHEN-THEN (arrange, act, assert) structure to keep each test focused and readable.
 *
 * Key notes:
 *   - Depends on the Microsoft Visual C++ Testing Framework and its runner; it has no main()
 *     and cannot be compiled or executed as a standalone program.
 */
#include "ObjectPoolTest.h"
#include "ObjectPool.h"
#include "Serial.h"
#include <stdexcept>
#include <memory>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

void ObjectPoolTest::setUp() { }
void ObjectPoolTest::tearDown() { }

void ObjectPoolTest::testSimple()
{
	Assert::IsTrue(0 < 1);
}

void ObjectPoolTest::testException()
{
	Assert::ExpectException<std::invalid_argument>(
		[] { throw std::invalid_argument{ "Error" }; });
}

void ObjectPoolTest::testCreation()
{
	// IF nothing

	// WHEN creating an ObjectPool
	ObjectPool<Serial> myPool;

	// THEN no exception is thrown
}

void ObjectPoolTest::testAcquire()
{
	// IF an ObjectPool has been created for Serial objects
	ObjectPool<Serial> myPool;
	// WHEN acquiring an object
	auto serial{ myPool.acquireObject() };
	// THEN we get a valid Serial object
	Assert::IsTrue(serial->getSerialNumber() >= 0);
}

void ObjectPoolTest::testExclusivity()
{
	// IF an ObjectPool has been created for Serial objects
	ObjectPool<Serial> myPool;
	// WHEN acquiring several objects from the pool
	const size_t numberOfObjectsToRetrieve{ 20 };
	set<unsigned> seenSerialNumbers;

	for (size_t i{ 0 }; i < numberOfObjectsToRetrieve; ++i) {
		auto nextSerial{ myPool.acquireObject() };
		seenSerialNumbers.insert(nextSerial->getSerialNumber());
	}

	// THEN all retrieved serial numbers are different.
	Assert::AreEqual(numberOfObjectsToRetrieve, seenSerialNumbers.size());
}

void ObjectPoolTest::testRelease()
{
	// IF an ObjectPool has been created for Serial objects
	ObjectPool<Serial> myPool;
	// AND we acquired and released 10 objects from the pool, while
	//     remembering their raw pointers
	const size_t numberOfObjectsToRetrieve{ 10 };
	// A set to remember all raw pointers that have been handed out by the pool.
	set<Serial*> retrievedSerialPointers;
	vector<shared_ptr<Serial>> retrievedSerials;
	for (size_t i{ 0 }; i < numberOfObjectsToRetrieve; ++i) {
		auto object{ myPool.acquireObject() };
		retrievedSerialPointers.insert(object.get());
		// Add the retrieved Serial to the vector to keep it 'alive'.
		retrievedSerials.push_back(object);
	}
	// Release all objects back to the pool.
	retrievedSerials.clear();

	// The above loop has created 10 Serial objects, with 10 different
	// addresses, and released all 10 Serial objects back to the pool.

	// WHEN again retrieving 10 objects from the pool, and
	//      remembering their raw pointers.
	set<Serial*> newlyRetrievedSerialPointers;
	for (size_t i{ 0 }; i < numberOfObjectsToRetrieve; ++i) {
		auto object{ myPool.acquireObject() };
		newlyRetrievedSerialPointers.insert(object.get());
		// Add the retrieved Serial to the vector to keep it 'alive'.
		retrievedSerials.push_back(object);
	}
	// Release all objects back to the pool.
	retrievedSerials.clear();

	// THEN all addresses of the 10 newly acquired objects must have been
	//      seen already during the first loop of acquiring 10 objects.
	//      This makes sure objects are properly re-used by the pool.
	Assert::IsTrue(retrievedSerialPointers == newlyRetrievedSerialPointers);
}
