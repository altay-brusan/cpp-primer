/*
 * Implementation for SpreadsheetCell.h - see the header for the conceptual notes.
 *
 * The `SpreadsheetCell::` prefix uses the scope resolution operator to tell the compiler
 * that these definitions belong to the class. The const qualifier from the declaration is
 * repeated on the definition; the access specifier is not.
 */

#include "SpreadsheetCell.h"

void SpreadsheetCell::setValue(double value)
{
	m_value = value;
}

double SpreadsheetCell::getValue() const
{
	return m_value;
}
