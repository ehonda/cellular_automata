#include "base_converter.h"

#include <stdexcept>

#include "cell.h"

namespace cellular_automata {
namespace integers {

BaseConverter::BaseConverter(long base)
	: _base(base)
{
	throwIfInvalidBase();
}

BaseConverter::BaseBRepresentation BaseConverter::getBaseBRepresentationFromInteger(long integer) const
{
	throwIfInvalidBase();
	throwIfInvalid(integer);

	BaseBRepresentation baseBRepresentation;
	long remainder;
	while (integer != 0)
	{
		remainder = integer % _base;
		integer -= remainder;
		integer /= _base;
		baseBRepresentation.emplace_back(remainder);
	}
	return baseBRepresentation;
}

BaseConverter::BaseBRepresentation BaseConverter::getBaseBRepresentationFromInteger(mpz_class integer) const {
	throwIfInvalid(integer);

	BaseBRepresentation baseBRepresentation;
	mpz_class remainder;
	while (integer != 0) {
		remainder = integer % _base;
		integer -= remainder;
		integer /= _base;
		baseBRepresentation.emplace_back(remainder.get_ui());
	}
	return baseBRepresentation;
}

long BaseConverter::getIntegerFromBaseBRepresentation(const BaseBRepresentation& baseBRepresentation) const {
	throwIfInvalidBase();
	throwIfInvalid(baseBRepresentation);

	long integer = 0;
	long factor = 1;
	for (const auto& digit : baseBRepresentation)
	{
		integer += factor * digit;
		factor *= _base;
	}
	return integer;
}

long BaseConverter::getIntegerFromCellNeighborhood(const std::vector<Cell>& cellNeighborhood) const {
	throwIfInvalid(cellNeighborhood);

	long integer = 0;
	long factor = 1;
	for (const auto& cell : cellNeighborhood) {
		integer += factor * cell.getState();
		factor *= _base;
	}
	return integer;
}

mpz_class BaseConverter::getMpzFromBaseBRepresentation(const BaseBRepresentation& baseBRepresentation) const {
	throwIfInvalid(baseBRepresentation);

	mpz_class integer = 0;
	mpz_class factor = 1;
	for (const auto& digit : baseBRepresentation) {
		integer += factor * digit;
		factor *= _base;
	}
	return integer;
}

void BaseConverter::throwIfInvalidBase() const
{
	if (_base < MIN_BASE)
		throw std::domain_error("The base for conversion must be at least 2.");
}

void BaseConverter::throwIfInvalid(long integer) const
{
	if (integer < MIN_INTEGER)
		throw std::domain_error("Negative integers are not supported by BaseConverter.");
}

void BaseConverter::throwIfInvalid(const mpz_class& integer) const {
	if (integer < MIN_INTEGER)
		throw std::domain_error("Negative integers are not supported by BaseConverter.");
}

void BaseConverter::throwIfInvalid(const BaseBRepresentation& baseBRepresentation) const
{
	for (const auto& digit : baseBRepresentation)
		if (digit < MIN_INTEGER || digit >= _base)
			throw std::domain_error
			("Base-B Representation to convert from has digits that are negative or greater or equal to base.");
}

void BaseConverter::throwIfInvalid(const std::vector<Cell>& cellNeighborhood) const {
	for (const auto& cell : cellNeighborhood)
		if (cell.getState() < MIN_INTEGER || cell.getState() >= static_cast<integers::state_t>(_base))
			throw std::domain_error("CellNeighborhood to convert from has digits that are negative or greater or equal to base.");
}

}
}
