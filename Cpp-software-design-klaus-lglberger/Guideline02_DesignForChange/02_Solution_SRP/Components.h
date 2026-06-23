/*
 * Guideline 2 - JSON and Serialization isolated as separate variation points (SOLUTION part 2)
 *
 * This header declares the two orthogonal aspects that used to live inside Document, now
 * extracted into their own small components. The JSON component and the Serialization
 * component each form a single "variation point": the one place where that kind of change
 * is expected. Switching to a different JSON library now touches only Components.cpp's
 * exportToJson(); changing the byte framing touches only serialize(). Neither change can
 * reach the Document hierarchy or each other.
 *
 * Key notes:
 *   - These are free functions, not member functions, so adding or changing an aspect does not
 *     force an edit to the Document classes (no recompile-the-world, no re-implement-in-every-derived).
 *   - They depend on Document's small public interface only, which is the necessary, intrinsic
 *     dependency - not an artificial one.
 *   - The DocumentType tag now lives next to serialization, the only aspect that needs it, instead
 *     of being a global enum that every document depends on.
 */

#pragma once

#include "Document.h"

#include <cstdint>
#include <string>
#include <vector>

// ---- JSON component: one variation point. Replace the body to swap "libraries". --------
std::string exportToJson(const Document& doc);

// ---- Serialization component: a separate, independent variation point. -----------------
std::vector<std::uint8_t> serialize(const Document& doc);
