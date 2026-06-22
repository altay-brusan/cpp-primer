/*
 * Chapter 31 - Compile-Time Debug Mode
 *
 * Shows the alternative to start-time debug mode: the trace code is selected with a
 * preprocessor symbol (DEBUG_MODE) and #ifdef blocks, so it is compiled into the program only
 * for a debug build and adds nothing to the release binary. When DEBUG_MODE is defined the
 * LOG() macro expands to a Logger::log() call; when it is not, LOG() expands to a no-op so
 * the calls vanish entirely.
 *
 * Key notes:
 *   - Trade-off: zero release-binary cost, but no way to enable tracing at a customer site.
 *   - Because LOG() can disappear, never place code with side effects needed for correctness
 *     inside a LOG() call - it would be stripped along with the macro, as the in-file warning notes.
 */

#include <print>
#include <fstream>
#include <string>
#include <chrono>
#include <iostream>
#include <exception>

using namespace std;

#define DEBUG_MODE

#ifdef DEBUG_MODE
	class Logger
	{
	public:
		template<typename... Args>
		static void log(const Args&... args)
		{
			ofstream logfile{ ms_debugFilename, ios_base::app };
			if (logfile.fail()) {
				println(cerr, "Unable to open debug file!");
				return;
			}
			print(logfile, "{:L} UTC: ", chrono::system_clock::now());
			// Use a fold-expression; see Chapter 26.
			(logfile << ... << args);
			logfile << endl;
		}

	private:
		static inline const string ms_debugFilename{ "debugfile.out" };
	};

	#define LOG(...) Logger::log(__func__, "(): ", __VA_ARGS__)
#else
	#define LOG(...) (void)0
#endif

// WARNING:
//		Be careful not to put any code that must be executed for correct program
//		functioning inside your LOG() calls. For example, a line as follows could
//		be asking for trouble:
//		    LOG("Result: ", calculateResult());
//		If DEBUG_MODE is not defined, the preprocessor replaces all LOG() calls with
//		no-ops, which means that the call to calculateResult() is removed as well!

class ComplicatedClass
{
	// Class details omitted for brevity.
};
ostream& operator<<(ostream& outStream, const ComplicatedClass& /* src */)
{
	outStream << "ComplicatedClass";
	return outStream;
}

class UserCommand
{
	// Class details not shown for brevity.
};
ostream& operator<<(ostream& outStream, const UserCommand& /* src */)
{
	outStream << "UserCommand";
	return outStream;
}



UserCommand getNextCommand(ComplicatedClass* /* obj */)
{
	UserCommand cmd;
	return cmd;
}

void processUserCommand(const UserCommand& /* cmd */)
{
	// Details omitted for brevity.
}

void trickyFunction(ComplicatedClass* obj)
{
	LOG("given argument: ", *obj);

	for (size_t i{ 0 }; i < 100; ++i) {
		UserCommand cmd{ getNextCommand(obj) };
		LOG("retrieved cmd ", i, ": ", cmd);

		try {
			processUserCommand(cmd);
		} catch ([[maybe_unused]] const exception& e) {
			LOG("received exception from processUserCommand(): ", e.what());
		}
	}
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
#ifdef DEBUG_MODE
	// Print the command-line arguments to the trace.
	for (size_t i{ 0 }; i < argc; ++i) {
		LOG("Argument: ", argv[i]);
	}
#endif

	ComplicatedClass obj;
	trickyFunction(&obj);

	// Rest of the function not shown.
}
