/*
 * Chapter 34 - Using a C Library Directly vs. Through a C++ Wrapper
 *
 * Driver for the mixing-C-and-C++ example. The first block (commented out)
 * shows the raw, procedural C style: paired lookup, connect, retrieve, and
 * manual free calls that are easy to get wrong. The second block shows the
 * C++ style using the WebHost facade, where construction, connection, and all
 * cleanup happen automatically via RAII, returning the page as a std::string.
 */

//#include "networklib.h"

#include "HostRecord.h"
#include "WebHost.h"
#include <print>

using namespace std;

int main()
{
	{ // C Style
		//HostHandle* myHost{ lookupHostByName("www.wrox.com") };
		//ConnectionHandle* myConnection{ connectToHost(myHost) };
		//char* result{ retrieveWebPage(myConnection, "/index.html") };

		//println("The result is:\n{}", result);

		//freeWebPage(result); result = nullptr;
		//closeConnection(myConnection); myConnection = nullptr;
		//freeHostHandle(myHost); myHost = nullptr;
	}

	{ // C++ Style
		WebHost myHost{ "www.wrox.com" };
		string result{ myHost.getPage("/index.html") };
		println("The result is:\n{}", result);
	}
}
