/*
 * Chapter 11 - Modules (9/10): Private Module Fragment + Pimpl
 *
 * Modules have a built-in way to hide implementation details: the *private
 * module fragment*, opened by `module :private;`. Anything below that line
 * is invisible to importers and changes to it don't trigger their rebuilds.
 *
 * Combined with the Pimpl idiom this gives you "header that never changes":
 *   - Public interface (above): Adder declares its methods and holds a
 *     unique_ptr to an opaque `Impl`.
 *   - Private fragment (below): `Adder::Impl` is fully defined, and
 *     Adder's bodies use it freely.
 *
 * Key notes:
 *   - `getImplementation()` returns an `Impl*`, but clients can't actually
 *     call anything on it - the type is incomplete from their side.
 *   - The same effect with classic headers requires a separate .cpp and a
 *     forward-declared `Impl` in the header. Private module fragments make
 *     it a single file.
 */
export module adder;

import std;

export class Adder
{
public:
	Adder();
	virtual ~Adder();
	int add(int a, int b) const;
private:
	class Impl;                    // forward-declared; opaque to importers
	std::unique_ptr<Impl> m_impl;

public:
	Impl* getImplementation() { return m_impl.get(); }
};

module :private;                   // <-- Boundary. Importers see nothing past this.

class Adder::Impl
{
public:
	~Impl()
	{
		std::println("Destructor of Adder::Impl");
	}

	int add(int a, int b) const
	{
		return a + b;
	}
};

Adder::Adder()
	: m_impl{ std::make_unique<Impl>() }
{
}

Adder::~Adder() {}

int Adder::add(int a, int b) const
{
	return m_impl->add(a, b);
}
