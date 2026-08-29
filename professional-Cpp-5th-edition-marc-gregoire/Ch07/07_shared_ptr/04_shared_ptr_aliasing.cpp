/*
 * Chapter 7 - shared_ptr / Aliasing
 *
 * A `shared_ptr` actually tracks TWO pointers: the "owned" pointer used for reference
 * counting, and the "stored" pointer returned by `get()` and `operator*`. The aliasing
 * constructor lets you share ownership of one object while exposing a pointer to a
 * different (typically sub-)object. The common use case is pointing at a member of a
 * larger object that the outer `shared_ptr` keeps alive.
 *
 * Key notes:
 *   - Form: `shared_ptr<U>{ outer_sp, &outer_sp->member }`. The outer `shared_ptr` keeps
 *     the parent alive; the new `shared_ptr<U>` exposes only the member.
 *   - The parent is destroyed only when EVERY participating `shared_ptr` (including the
 *     aliasing one) is gone.
 *   - The stored pointer can be any address whose lifetime is bound to the owned object -
 *     a member, a subobject in an inheritance hierarchy, an element in an owned array.
 *   - Useful for handing out a "view" pointer to a piece of state without leaking the
 *     whole containing object's type.
 */

/*
 * ===========================================================================
 * Chapter 7 - shared_ptr / The Aliasing Constructor
 * ===========================================================================
 *
 * 1. WHAT A shared_ptr REALLY IS
 * ---------------------------------------------------------------------------
 * Forget the name for a moment. A shared_ptr is a struct with exactly two
 * fields:
 *
 *     template <typename T>
 *     class shared_ptr
 *     {
 *         T*            m_stored;   // what get() and operator* give you
 *         ControlBlock* m_control;  // where the reference count lives
 *     };
 *
 * The control block is a separate little heap object holding roughly:
 *
 *     struct ControlBlock
 *     {
 *         long    strong_count;  // how many shared_ptr instances share this
 *         long    weak_count;
 *         Deleter deleter;       // what to run when strong hits 0
 *         void*   owned;         // the pointer the deleter will be given
 *     };
 *
 * Notice that `owned` and `m_stored` are two DIFFERENT fields. In normal use
 * they hold the same address, so you never think about the distinction. The
 * aliasing constructor is simply the one place in the language where you are
 * allowed to set them to different things.
 *
 *
 * 2. THE PICTURE
 * ---------------------------------------------------------------------------
 *
 *   foo                                Foo object (heap)
 *   +--------------+                   +-----------------+
 *   | stored   ----|-----------------> | m_data = 42     |
 *   | control  --+ |                   +-----------------+
 *   +------------|-+                     ^           ^
 *                |                       |           |
 *                |   control block       |           |
 *                +-> +-----------------+ |           |
 *                |   | strong  = 2     | |           |
 *                |   | weak    = 0     | |           |
 *                |   | owned   --------+-+           |
 *                |   | deleter = delete|             |
 *                |   +-----------------+             |
 *   aliasing     |                                   |
 *   +--------------+                                 |
 *   | stored   ----|---------------------------------+  (&foo->m_data, an
 *   | control  --+ |                                     address INSIDE Foo)
 *   +------------|-+
 *                |
 *                +-> (the very same control block)
 *
 * Both shared_ptrs point at the same control block, so strong == 2. But
 * aliasing.get() returns &foo->m_data, an int*. When the count drops to zero
 * the deleter runs on `owned`, which is still the whole Foo. The int* is never
 * deleted, never even looked at by the destructor machinery.
 *
 * That is the entire feature. Nothing is allocated when you build an alias.
 * One atomic increment happens, and you get to choose what get() returns.
 * Because of this, U needs no relationship to T at all - no base class, no
 * virtual destructor.
 *
 *
 * 3. RUNTIME TRACE
 * ---------------------------------------------------------------------------
 *
 *     {
 *         auto foo{ make_shared<Foo>(42) };            // strong = 1
 *         {
 *             shared_ptr<int> a{ foo, &foo->m_data };  // strong = 2
 *             *a = 99;                                 // writes foo->m_data
 *         }                                            // a dies:   strong = 1
 *         // foo->m_data is now 99, the Foo is still alive
 *     }                                                // foo dies: strong = 0
 *                                                      //   -> delete on Foo*
 *
 * And the reverse order works identically:
 *
 *     shared_ptr<int> a;
 *     {
 *         auto foo{ make_shared<Foo>(42) };            // strong = 1
 *         a = shared_ptr<int>{ foo, &foo->m_data };    // strong = 2
 *     }                              // foo dies: strong = 1, the Foo SURVIVES
 *     *a = 7;                        // still perfectly valid
 *
 * This second case is the point of the feature. The Foo outlives the only
 * variable that ever named it, because an alias is holding it up.
 *
 *
 * ===========================================================================
 * EXAMPLE 1 - ROWS OF AN IMAGE (zero-copy slices)
 * ===========================================================================
 *
 * THE SITUATION. You decode a video frame. The pixels live in one big
 * vector<uint8_t> inside a DecodedFrame. You want to hand individual rows to
 * worker threads.
 *
 *     struct DecodedFrame
 *     {
 *         std::vector<std::uint8_t> pixels;   // width * height bytes
 *         int width;
 *         int height;
 *     };
 *
 * WITHOUT ALIASING, EVERY OPTION IS BAD:
 *
 *   (a) Copy each row into its own buffer. Wasteful, and the whole reason you
 *       decoded into one buffer is gone.
 *   (b) Pass a raw uint8_t*. Fast, but now YOU must guarantee the frame
 *       outlives every worker. If a worker is slow and the frame is dropped,
 *       you get a use-after-free that only shows up under load.
 *   (c) Pass shared_ptr<DecodedFrame> plus a row index to every worker. Works,
 *       but now every worker's signature depends on DecodedFrame. A generic
 *       blur routine should not need to know your video pipeline's types.
 *
 * WITH ALIASING:
 *
 *     std::shared_ptr<std::uint8_t> get_row(
 *         const std::shared_ptr<DecodedFrame>& frame, int y)
 *     {
 *         std::uint8_t* row_start =
 *             frame->pixels.data() + std::size_t(y) * frame->width;
 *
 *         return { frame, row_start };
 *         //       ^^^^^  ^^^^^^^^^
 *         //       |      what get() will return
 *         //       whose lifetime we are borrowing
 *     }
 *
 *     void blur(std::shared_ptr<std::uint8_t> row, int width);
 *     // ^ no DecodedFrame anywhere in sight
 *
 * The worker sees a pointer to bytes. It has no idea a frame exists. But the
 * frame cannot be destroyed while that worker holds its row, because the
 * frame's control block still counts it. Ten rows handed out means strong ==
 * 11. The frame is freed the instant the last worker returns, wherever that
 * happens to be, with no cleanup code written anywhere.
 *
 * THE GOTCHA IS REAL. The alias points at pixels.data(), which is a heap
 * buffer OWNED BY the vector, not the vector itself. If anyone calls
 * frame->pixels.resize(...) or push_back(...), the vector reallocates and
 * frees the old buffer. Every row alias now dangles, even though the
 * DecodedFrame is alive and the refcount is perfectly happy. Aliasing binds
 * you to an ADDRESS, not to a logical member. Only alias into storage that is
 * guaranteed not to move.
 *
 *
 * ===========================================================================
 * EXAMPLE 2 - MEMORY-MAPPED FILE (last user wins)
 * ===========================================================================
 *
 * WHAT mmap DOES. It asks the OS to make a file appear as a region of memory.
 * You get a void*. Reading through it reads the file. When you are finished
 * you must call munmap(base, length) or you leak the mapping.
 *
 * THE LIFETIME PROBLEM. A 4 GB data file contains a header and a million
 * records. You want to give different parts of your program pointers to
 * individual records. Every one of those pointers is only valid while the
 * mapping exists. Tracking "am I the last user of this mapping?" by hand
 * across threads and callbacks is exactly the bookkeeping people get wrong.
 *
 * STEP ONE - make the mapping itself a shared_ptr with a custom deleter:
 *
 *     std::shared_ptr<void> map_file(const char* path)
 *     {
 *         int fd = ::open(path, O_RDONLY);
 *         struct stat st{};
 *         ::fstat(fd, &st);
 *         void* base = ::mmap(nullptr, st.st_size,
 *                             PROT_READ, MAP_PRIVATE, fd, 0);
 *         ::close(fd);   // the mapping survives closing the fd
 *
 *         auto len = st.st_size;
 *         return std::shared_ptr<void>{ base,
 *                    [len](void* p) { ::munmap(p, len); } };
 *         //          ^^^^  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *         //          owned pointer, and what to run instead of `delete`
 *     }
 *
 * The deleter captures the length because munmap needs it. That alone is a
 * nice trick: it turns a C resource into an RAII object.
 *
 * STEP TWO - hand out records as aliases:
 *
 *     struct Header { std::uint32_t magic, record_count, records_offset; };
 *     struct Record { std::uint64_t id; double value; };
 *
 *     std::shared_ptr<const Record> get_record(
 *         const std::shared_ptr<void>& mapping, std::size_t i)
 *     {
 *         auto* bytes = static_cast<const std::byte*>(mapping.get());
 *         auto* hdr   = reinterpret_cast<const Header*>(bytes);
 *         auto* first = reinterpret_cast<const Record*>(
 *                           bytes + hdr->records_offset);
 *         return { mapping, first + i };
 *     }
 *
 * A caller holding a single shared_ptr<const Record> is holding up the entire
 * 4 GB mapping. When the last record reference anywhere in the program is
 * dropped, munmap runs. Nobody wrote cleanup code. Nobody wrote an
 * "is it still in use?" flag.
 *
 * The flip side is the danger: one forgotten record pins 4 GB resident.
 * Aliases keep alive far more than they appear to.
 *
 *
 * ===========================================================================
 * EXAMPLE 3 - A shared_ptr THAT OWNS NOTHING
 * ===========================================================================
 *
 * Sometimes an API insists on shared_ptr<T>, but your object is a global, a
 * static, or a member of something with a longer lifetime. It must NOT be
 * deleted. Alias off a default-constructed, EMPTY shared_ptr:
 *
 *     Logger& global_logger();   // function-local static, lives forever
 *
 *     std::shared_ptr<Logger> borrowed{ std::shared_ptr<Logger>{},
 *                                       &global_logger() };
 *
 * An empty shared_ptr has m_control == nullptr. The alias copies that null
 * control block and takes your chosen stored pointer. So:
 *
 *   - borrowed.get()        returns a valid Logger*
 *   - borrowed.use_count()  returns 0
 *   - copying it increments nothing; destroying it deletes nothing, ever
 *
 * This is standard-blessed, not a hack. But treat it as a last resort. Anyone
 * reading shared_ptr<Logger> in a signature reasonably assumes ownership is
 * being shared, and here it is not. If that object ever does get destroyed,
 * the type gave you no protection at all.
 *
 *
 * ===========================================================================
 * EXAMPLE 4 - EXPOSING ONE MEMBER
 * ===========================================================================
 *
 *     class Connection
 *     {
 *     public:
 *         struct Stats
 *         {
 *             std::atomic<std::uint64_t> bytes_sent{ 0 };
 *             std::atomic<std::uint64_t> bytes_received{ 0 };
 *         };
 *         Stats& stats() { return m_stats; }
 *
 *     private:
 *         Socket m_socket;
 *         Stats  m_stats;
 *     };
 *
 *     std::shared_ptr<Connection::Stats> stats_view(
 *         const std::shared_ptr<Connection>& conn)
 *     {
 *         return { conn, &conn->stats() };
 *     }
 *
 * A metrics thread polls counters once a second. What it needs is two atomics.
 * What it must not have is the ability to touch the socket. Give it a
 * shared_ptr<Stats> and:
 *
 *   - it physically cannot reach m_socket, because it lacks the Connection type
 *   - the Connection cannot be destroyed mid-read, because the alias holds it
 *   - the connection's owner can drop its own shared_ptr at any time and
 *     nothing breaks
 *
 * This one is safe in a way Example 1 is not: m_stats is a direct member, so
 * its address is fixed for the entire lifetime of the Connection. That fixed
 * address is exactly the property to look for when choosing what to alias.
 *
 *
 * ===========================================================================
 * WHEN TO REACH FOR IT
 * ===========================================================================
 *   - The consumer needs a PIECE of something and should not know about the
 *     whole thing.
 *   - The resource is expensive or C-style, and you want its release to be
 *     automatic and last-user-wins.
 *   - A part must keep the whole alive, and you do not want to hand-write
 *     that rule.
 *
 * WHEN NOT TO
 *   - If the address can move (vector reallocation, std::string SSO, a deque
 *     element after insertion), do not alias into it.
 *   - If the consumer only borrows for the duration of a call and cannot
 *     outlive the owner, pass a plain reference or a span. Aliasing costs an
 *     atomic increment plus decrement, and it hides how much memory is held.
 *   - If you alias into an object whose parent lifetime rules you do not
 *     control, you are just moving the dangling problem somewhere harder to
 *     see.
 *
 *
 * ===========================================================================
 * TWO DETAILS FOR LATER
 * ===========================================================================
 * COMPARISON IS ASYMMETRIC. operator== compares STORED pointers;
 * owner_before() compares CONTROL BLOCKS. Two aliases into different members
 * of the same Foo compare unequal but are equivalent owners. This matters the
 * day you use shared_ptr as a std::map key or in a std::set.
 *
 * C++20 ADDED A MOVE VERSION: shared_ptr(shared_ptr&& r, element_type* p),
 * which steals the control block instead of incrementing it:
 *
 *     auto row = std::shared_ptr<std::uint8_t>{ std::move(frame), row_start };
 *     // frame is now empty; no atomic increment happened
 *
 * Use it when you are transferring rather than sharing.
 * ===========================================================================
 * 
 * 
 * #include <atomic>
 * #include <cstdint>
 * #include <memory>
 * #include <cassert>
 * using namespace std;
 *	class Foo
	{
	public:
		Foo(int value) : m_data{ value } { }
		int m_data;
	};

	// Example 4, trimmed down so it actually compiles.
	class Connection
	{
	public:
		struct Stats
		{
			atomic<uint64_t> bytes_sent{ 0 };
			atomic<uint64_t> bytes_received{ 0 };
		};

		Stats& stats() { return m_stats; }

	private:
		int   m_socket_fd{ -1 };  // stands in for a real Socket
		Stats m_stats;
	};

	shared_ptr<Connection::Stats> stats_view(const shared_ptr<Connection>& conn)
	{
		// Safe: m_stats is a direct member, so its address is fixed for the
		// whole lifetime of the Connection.
		return { conn, &conn->stats() };
	}

	int main()
	{
		// --- the basic form -----------------------------------------------
		auto foo{ make_shared<Foo>(42) };
		assert(foo.use_count() == 1);
		{
			auto aliasing{ shared_ptr<int>{ foo, &foo->m_data } };
			assert(foo.use_count() == 2);       // one control block, two owners
			assert(aliasing.get() == &foo->m_data);
			*aliasing = 99;                     // writes straight into the Foo
		}                                       // alias dies, Foo does not
		assert(foo.use_count() == 1);
		assert(foo->m_data == 99);

		// --- the alias outliving its parent handle ------------------------
		shared_ptr<int> survivor;
		{
			auto tmp{ make_shared<Foo>(7) };
			survivor = shared_ptr<int>{ tmp, &tmp->m_data };
		}                                       // tmp gone, Foo still alive
		assert(*survivor == 7);
		*survivor = 8;                          // still perfectly valid

		// --- handing out just one member ----------------------------------
		auto conn{ make_shared<Connection>() };
		auto metrics{ stats_view(conn) };       // sees Stats, never the socket
		metrics->bytes_sent.fetch_add(1024);
		assert(conn.use_count() == 2);
		conn.reset();                           // owner walks away...
		assert(metrics->bytes_sent.load() == 1024);   // ...Connection lives on

		// --- non-owning alias ---------------------------------------------
		static Foo forever{ 1 };
		shared_ptr<Foo> borrowed{ shared_ptr<Foo>{}, &forever };
		assert(borrowed.get() == &forever);
		assert(borrowed.use_count() == 0);      // owns nothing, deletes nothing
	}
 */

#include <atomic>
#include <cassert>
#include <cstdint>
#include <memory>



#include <memory>

using namespace std;

class Foo
{
public:
	Foo(int value) : m_data{ value } { }
	int m_data;
};

int main()
{
	auto foo{ make_shared<Foo>(42) };
	// Aliasing ctor: shares foo's control block (and thus its lifetime) but exposes
	// the address of foo->m_data. The Foo dies only when BOTH `foo` and `aliasing` are gone.
	auto aliasing{ shared_ptr<int>{ foo, &foo->m_data } };
}