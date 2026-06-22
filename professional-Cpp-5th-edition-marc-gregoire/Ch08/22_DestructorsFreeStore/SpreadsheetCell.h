#pragma once

/*
 * Chapter 8 - Object Destruction (free store)
 *
 * Same destructor as folder 21. The point of this folder is the driver - free-store
 * objects do not die at scope exit. The destructor only runs when you call `delete` on
 * the pointer (or `delete[]` for an array). If you forget, the object lives until the
 * process ends and any work the destructor would have done is silently skipped.
 *
 * Key notes:
 *   - `delete p;` invokes `~SpreadsheetCell()` and then frees the storage.
 *   - Use `delete[]` for memory obtained with `new[]`. Mixing the two is undefined
 *     behaviour.
 *   - Setting the pointer to nullptr after `delete` is hygiene, not strictly required.
 *   - Prefer smart pointers so this discipline becomes automatic and exception-safe.
 *   - When the destructor would manage owned resources (memory, file handles, sockets),
 *     forgetting `delete` is a real leak, not just a missed printout.
 */

#include <string>
#include <string_view>

class SpreadsheetCell
{
public:
	SpreadsheetCell() = default;
	SpreadsheetCell(double initialValue);
	SpreadsheetCell(std::string_view initialValue);
	SpreadsheetCell(const SpreadsheetCell& src);

	// Destructor.
	~SpreadsheetCell();

	void setValue(double value);
	double getValue() const;

	void setString(std::string_view value);
	std::string getString() const;

private:
	std::string doubleToString(double value) const;
	double stringToDouble(std::string_view value) const;

	double m_value{ 0 };
};
