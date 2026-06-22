/*
 * Chapter 33 - Adapter Pattern in Action
 *
 * Driver for the Adapter pattern. It creates an AdaptedLogger and logs a message
 * through the simplified adapted interface; behind the scenes the adapter routes
 * the call to the wrapped Logger. This shows the client using existing
 * functionality through a new, more convenient interface.
 *
 * Key notes:
 *   - Contains main(); run as a standalone program.
 */

#include "LoggerAdapter.h"

int main()
{
	AdaptedLogger logger;
	logger.log("Testing the logger.");
} 
