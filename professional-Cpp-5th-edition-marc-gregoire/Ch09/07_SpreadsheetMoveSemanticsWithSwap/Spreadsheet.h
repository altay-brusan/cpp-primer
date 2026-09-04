/*
 * Chapter 9 - Move Constructor and Move Assignment in Terms of Swap
 *
 * The move ctor and move assignment can be written purely in terms of `swap()`,
 * which removes the cleanup() / moveFrom() helpers entirely. The move ctor swaps
 * a default-constructed `*this` with `src`; the move-assignment swaps `*this` with
 * a freshly-moved copy of `rhs`. Whatever ends up holding the old resources is
 * destroyed when its scope ends, doing the cleanup automatically.
 *
 * Key notes:
 *   - Add a new data member? Update swap() once; both move operations follow for free.
 *   - The move constructor begins by default-initializing `*this` (zero/null members),
 *     then swaps. After the swap, `*this` owns what was in `src` and `src` owns the
 *     null/zero state.
 *   - The move assignment is `auto moved{ std::move(rhs) }; swap(moved); return *this;`
 *     - the temporary `moved` takes the old contents and is destroyed on exit, freeing
 *     any old resources without manual cleanup.
 *   - swap() must be `noexcept`; the move operations rely on it never throwing.
 *   - This is the same copy-and-swap discipline used for copy assignment, applied to
 *     move.
 *
 * operator= is ONLY used when BOTH sides ALREADY EXIST (are already initialized).
 *
 * When you initialize a fresh (new) variable using a temporary object or a
 * function return value, C++ calls a Constructor, NOT operator=.
 *
 * -----------------------------------------------------------------------------
 * The Fundamental Rule:
 * -----------------------------------------------------------------------------
 *   - Creating a fresh variable?
 *     -> Calls a Constructor (Copy or Move Constructor).
 *
 *   - Assigning to a variable that ALREADY exists?
 *     -> Calls operator= (Copy or Move Assignment Operator).
 *
 * -----------------------------------------------------------------------------
 * Step-by-Step Code Examples:
 * -----------------------------------------------------------------------------
 *
 * Scenario 1: Initializing a FRESH Variable (Calls Constructor)
 * Even if you use the '=' sign, if you are declaring a new variable on the left,
 * it calls a constructor:
 *
 *   // 1. Fresh variable initialized using a temporary object:
 *   Spreadsheet s1 = Spreadsheet{ 50, 50 }; 
 *   // ^ Calls MOVE CONSTRUCTOR (or is completely elided/optimized out). NOT operator=!
 *
 *   // 2. Fresh variable initialized using a function result:
 *   Spreadsheet s2 = createSheet(); 
 *   // ^ Calls MOVE CONSTRUCTOR (or elided). NOT operator=!
 *
 * Scenario 2: Re-assigning an EXISTING Variable (Calls operator=)
 * operator= is ONLY called when the variable on the left was already created on
 * a previous line:
 *
 *   Spreadsheet s1{ 10, 10 }; // s1 ALREADY exists here
 *   
 *   // ... later in the code ...
 *   
 *   // NOW operator= is called because s1 already exists!
 *   s1 = Spreadsheet{ 50, 50 }; 
 *   // ^ Calls MOVE ASSIGNMENT OPERATOR (operator=)
 *
 * -----------------------------------------------------------------------------
 * Summary Checklist (Look at the left side of the line):
 * -----------------------------------------------------------------------------
 *   - Spreadsheet s1 = ...        | New variable declaration | Move / Copy Constructor
 *   - Spreadsheet s1{ ... };      | New variable declaration | Direct / Move Constructor
 *   - s1 = ... (already created)  | Updating existing object | Move / Copy operator=
 *
 *
 *
 * Whether the Move Assignment Operator or Copy Assignment Operator is selected
 * depends entirely on whether the right-hand side (RHS) value is an lvalue or an rvalue.
 *
 * -----------------------------------------------------------------------------
 * The Selection Rule:
 * -----------------------------------------------------------------------------
 *   - RHS is an lvalue (a named variable with an identifiable memory address that
 *     persists beyond the statement line)
 *     -> Calls Copy Assignment: operator=(const Spreadsheet&)
 *
 *   - RHS is an rvalue (a temporary object, a function return value, or an
 *     lvalue explicitly cast via std::move)
 *     -> Calls Move Assignment: operator=(Spreadsheet&&)
 *
 * -----------------------------------------------------------------------------
 * Examples in Code (Assuming s1 already exists in memory: Spreadsheet s1{ 10, 10 };):
 * -----------------------------------------------------------------------------
 *
 * 1. Triggers Copy Assignment (RHS is an Lvalue)
 *
 *    Spreadsheet s2{ 20, 20 }; // s2 has a name and stays alive
 *
 *    s1 = s2; 
 *    // ^ 's2' is an lvalue.
 *    // Calls: operator=(const Spreadsheet&)
 *    // 's2' must remain untouched and valid, so its data MUST be copied.
 *
 * 2. Triggers Move Assignment (RHS is an Rvalue)
 *
 *    // Case A: Temporary / Anonymous object
 *    s1 = Spreadsheet{ 30, 30 }; 
 *    // ^ Temporary object dies at the end of this line anyway.
 *    // Calls: operator=(Spreadsheet&&)
 *
 *    // Case B: Explicit std::move()
 *    Spreadsheet s3{ 40, 40 };
 *    s1 = std::move(s3); 
 *    // ^ std::move converts 's3' (lvalue) into an rvalue reference.
 *    // Calls: operator=(Spreadsheet&&)
 *    // s3's resources are stolen; s3 is left in a valid, empty state.
 *
 *    // Case C: Function returning by value
 *    s1 = makeSheet(); 
 *    // ^ The returned temporary is an rvalue.
 *    // Calls: operator=(Spreadsheet&&)
 *
 * -----------------------------------------------------------------------------
 * Summary Table:
 * -----------------------------------------------------------------------------
 *   Statement                | RHS Category            | Which operator= is called? | Why?
 *   --------------------------------------------------------------------------------------------------------------------
 *   s1 = s2;                 | Lvalue (named object)   | Copy Assignment           | s2 needs to keep its data intact for later use.
 *   s1 = std::move(s2);      | Rvalue (cast std::move) | Move Assignment           | You explicitly told the compiler s2 can be stolen from.
 *   s1 = Spreadsheet{5, 5};  | Rvalue (temporary)      | Move Assignment           | The temporary object dies immediately; stealing is safe.
 *   s1 = createSheet();      | Rvalue (returned temp)  | Move Assignment           | Temporary return value dies at the end of the statement.
 */


#pragma once

#include "SpreadsheetCell.h"
#include <cstddef>

class Spreadsheet
{
public:
	Spreadsheet(std::size_t width, std::size_t height);
	Spreadsheet(const Spreadsheet& src);
	Spreadsheet(Spreadsheet&& src) noexcept; // Move constructor
	~Spreadsheet();

	Spreadsheet& operator=(const Spreadsheet& rhs);
	Spreadsheet& operator=(Spreadsheet&& rhs) noexcept;  // Move assignment

	void setCellAt(std::size_t x, std::size_t y, const SpreadsheetCell& cell);
	SpreadsheetCell& getCellAt(std::size_t x, std::size_t y);

	void swap(Spreadsheet& other) noexcept;

private:
	void verifyCoordinate(std::size_t x, std::size_t y) const;

	std::size_t m_width{ 0 };
	std::size_t m_height{ 0 };
	SpreadsheetCell** m_cells{ nullptr };
};

void swap(Spreadsheet& first, Spreadsheet& second) noexcept;
