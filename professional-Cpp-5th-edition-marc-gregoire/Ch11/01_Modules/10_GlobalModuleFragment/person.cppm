/*
 * Chapter 11 - Modules (10/10): Global Module Fragment
 *
 * Modules don't allow `#include` after the module declaration, because
 * macros and other preprocessor effects don't compose with module rules.
 * If you must include legacy headers (a C library, an old in-house header,
 * a header that hasn't been modularized yet), put them in the *global module
 * fragment* - the section before `export module ...`.
 *
 * Structure:
 *   1. `module;` opens the global module fragment.
 *   2. `#include`s for legacy headers go here.
 *   3. `export module person;` ends the fragment and starts the named module.
 *
 * Key notes:
 *   - Declarations from the included headers are attached to the *global*
 *     module, not to `person`. That means they are NOT re-exported and
 *     names from `<cassert>` (like `assert`) are not visible to importers.
 *   - For Standard Library headers, `import std;` is the modern alternative
 *     - cleaner, faster, and no GMF needed.
 */
module;                // Start of the global module fragment
#include <cassert>     // Include legacy header files here

export module person;  // Named module declaration ends the GMF

import std;

export class Person
{
	/* ... */
};
