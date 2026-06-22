/*
 * Chapter 30 - Declaring a Test Class with the Microsoft Visual C++ Testing Framework
 *
 * This header declares the test fixture for the ObjectPool using the Microsoft Visual C++
 * Testing Framework. TEST_CLASS defines a group of related tests, TEST_CLASS_INITIALIZE and
 * TEST_CLASS_CLEANUP register setup and teardown hooks that run around the suite, and each
 * TEST_METHOD declares one individual unit test that the test runner will discover and
 * execute. This shows how a framework lets you describe tests declaratively while it handles
 * running them, reporting pass and fail results, and isolating each test.
 *
 * Key notes:
 *   - Requires the Visual Studio test framework header CppUnitTest.h and its test runner; it
 *     does not build or run as a standalone console program.
 */
#pragma once

#include <CppUnitTest.h>

TEST_CLASS(ObjectPoolTest)
{
public:
	TEST_CLASS_INITIALIZE(setUp);
	TEST_CLASS_CLEANUP(tearDown);

	TEST_METHOD(testSimple);  // Your first test!
	TEST_METHOD(testException);
	TEST_METHOD(testCreation);
	TEST_METHOD(testAcquire);
	TEST_METHOD(testExclusivity);
	TEST_METHOD(testRelease);
};
