#pragma once

#include <vector>

#include "gmpxx.h"

//Begin forward definitions
namespace cellular_automata {
class Cell;
}
//End forward definitions

namespace cellular_automata {
namespace integers {

class BaseConverter {
public:
	using BaseBRepresentation = std::vector<long>;
	static const long MIN_BASE = 2;
	static const long MIN_INTEGER = 0;

	BaseConverter(long base);

	BaseBRepresentation getBaseBRepresentationFromInteger(long integer) const;
	BaseBRepresentation getBaseBRepresentationFromInteger(mpz_class integer) const;

	long getIntegerFromBaseBRepresentation(const BaseBRepresentation& baseBRepresentation) const;
	long getIntegerFromCellNeighborhood(const std::vector<Cell>& cellNeighborhood) const;
	mpz_class getMpzFromBaseBRepresentation(const BaseBRepresentation& baseBRepresentation) const;

private:
	void throwIfInvalidBase() const;
	void throwIfInvalid(long integer) const;
	void throwIfInvalid(const mpz_class& integer) const;
	void throwIfInvalid(const BaseBRepresentation& baseBRepresentation) const;
	void throwIfInvalid(const std::vector<Cell>& cellNeighborhood) const;

	long _base;
};

}
}
