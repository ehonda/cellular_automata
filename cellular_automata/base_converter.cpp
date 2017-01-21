#include "base_converter.h"

#include <stdexcept>

namespace cellular_automata
{
namespace integers
{

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

long BaseConverter::getIntegerFromBaseBRepresentation(const BaseBRepresentation& baseBRepresentation) const
{
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

void BaseConverter::throwIfInvalid(const BaseBRepresentation& baseBRepresentation) const
{
	for (const auto& digit : baseBRepresentation)
		if (digit < MIN_INTEGER || digit >= _base)
			throw std::domain_error
			("Base-B Representation to convert from has digits that are negative or greater or equal to base.");
}

}
}
