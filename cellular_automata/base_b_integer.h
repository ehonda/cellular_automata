#pragma once

#include <vector>

#include "gmpxx.h"

#include "type_definitions.h"

namespace cellular_automata {
namespace integers {

class BaseBInteger
{
public:
	using BaseBRepresentation = std::vector<long>;
	static const long DEFAULT_BASE = 10;
	static const mpz_class DEFAULT_MPZ;
	static const BaseBRepresentation DEFAULT_BASE_B_REPRESENTATION;

	BaseBInteger();
	BaseBInteger(long base, const mpz_class& integer);
	BaseBInteger(long base, const BaseBRepresentation& baseBRepresentation);

	long getBase() const noexcept;
	const mpz_class& getInteger() const noexcept;
	const BaseBRepresentation& getBaseBRepresentation() const noexcept;
	long getDigitAt(size_t index) const noexcept;

	bool operator==(const BaseBInteger& other) const noexcept;
	bool operator!=(const BaseBInteger& other) const noexcept;

private:
	long _base;
	mpz_class integer_;
	BaseBRepresentation _baseBRepresentation;
};

}
}
