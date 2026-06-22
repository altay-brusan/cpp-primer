/*
 * Chapter 32 - Resource Acquisition Is Initialization (RAII)
 *
 * Implements a File RAII class that wraps a C-style std::FILE handle and guarantees the
 * file is closed when the wrapper goes out of scope. The constructor acquires the
 * resource and the destructor releases it via reset(). Copy operations are deleted (RAII
 * types typically own a unique resource), while move construction and move assignment
 * transfer ownership using std::exchange. get(), release(), and reset() mirror the API
 * of std::unique_ptr.
 *
 * Key notes:
 *   - Cleanup happens deterministically at scope exit, even when an exception unwinds.
 *   - Always give an RAII instance a name; an unnamed temporary is destroyed immediately.
 */
#include <print>
#include <cstdio>
#include <utility>

#if defined(_MSC_VER)
	// Disable the following Microsoft Visual C++ warning for this example:
	// C4996: 'fopen': This function or variable may be unsafe. Consider using fopen_s instead.
	#pragma warning( disable : 4996)
#endif

class File final
{
public:
	explicit File(std::FILE* file) : m_file{ file } { }
	~File() { reset(); }

	// Prevent copy construction and copy assignment.
	File(const File& src) = delete;
	File& operator=(const File& rhs) = delete;

	// Allow move construction.
	File(File&& src) noexcept : m_file{ std::exchange(src.m_file, nullptr) }
	{
	}

	// Allow move assignment.
	File& operator=(File&& rhs) noexcept
	{
		if (this != &rhs) {
			reset();
			m_file = std::exchange(rhs.m_file, nullptr);
		}
		return *this;
	}

	// get(), release(), and reset()
	std::FILE* get() const noexcept { return m_file; }

	[[nodiscard]] std::FILE* release() noexcept
	{
		return std::exchange(m_file, nullptr);
	}
	
	void reset(std::FILE* file = nullptr) noexcept
	{
		if (m_file) { std::fclose(m_file); }
		m_file = file;
	}

private:
	std::FILE* m_file{ nullptr };
};

int main()
{
	File myFile{ std::fopen("input.txt", "r") };
}
