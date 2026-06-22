/*
 * Chapter 31 - Ring Buffer for In-Memory Debug Traces
 *
 * Declares a fixed-size circular (ring) buffer for trace messages. Rather than writing traces
 * to disk continuously, the program keeps only the most recent N entries in memory; when the
 * buffer fills, new entries overwrite the oldest, so the latest history is always available to
 * dump after a bug occurs. addEntry() is a variadic template that formats all arguments (with a
 * timestamp) into one string; operator<< streams the whole buffer in chronological order, and an
 * optional output stream can echo entries live as they are added.
 *
 * Key notes:
 *   - Storage is a std::vector<std::string> sized once in the constructor; m_next marks the next
 *     write slot and m_wrapped records whether the buffer has cycled, which operator<< needs to
 *     print entries oldest-first.
 *   - For multithreaded use the buffer would need locking and per-entry thread IDs; this version
 *     is single-threaded for clarity.
 */

#pragma once

#include <print>
#include <vector>
#include <string>
#include <chrono>
#include <iostream>
#include <sstream>
#include <cstddef>

// Provides a simple ring buffer for messages. The client specifies the number
// of entries in the constructor, and adds messages with the addEntry()
// member function. Once the number of entries exceeds the number allowed, new
// entries overwrite the oldest entries in the buffer.
//
// The buffer also provides the option to output entries to a stream as
// they are added to the buffer. The client can specify an output stream
// in the constructor, and can reset it with the setOutput() member function.
// 
// Finally, the operator<< streams the entire buffer to an output stream.
class RingBuffer final
{
public:
	// Constructs a ring buffer with space for numEntries.
	// Entries are written to *outStream as they are queued (optional).
	explicit RingBuffer(std::size_t numEntries = DefaultNumEntries,
		std::ostream* outStream = nullptr);

	// Adds the string to the ring buffer, possibly overwriting the
	// oldest string in the buffer (if the buffer is full).
	template<typename... Args>
	void addEntry(const Args&... args)
	{
		std::ostringstream oss;
		std::print(oss, "{:L} UTC: ", std::chrono::system_clock::now());
		// Use a fold-expression; see Chapter 26.
		(oss << ... << args);
		addStringEntry(std::move(oss).str());
	}

	// Streams the buffer entries, separated by newlines, to outStream.
	friend std::ostream& operator<<(std::ostream& outStream, RingBuffer& rb);

	// Streams entries as they are added to the given stream.
	// Specify nullptr to disable this feature.
	// Returns the old output stream.
	std::ostream* setOutput(std::ostream* newOutStream);

private:
	std::vector<std::string> m_entries;
	std::vector<std::string>::iterator m_next;

	std::ostream* m_outStream{ nullptr };
	bool m_wrapped{ false };

	static constexpr std::size_t DefaultNumEntries{ 500 };

	void addStringEntry(std::string entry);
};
