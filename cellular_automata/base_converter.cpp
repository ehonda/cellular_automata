#include "base_converter.h"

namespace cellular_automata
{
namespace integers
{

BaseConverter::BaseConverter(long base)
	: _base(base)
{
}

BaseConverter::BaseBRepresentation BaseConverter::getBaseBRepresentationFromInteger(long integer) const
{
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
	long integer = 0;
	long factor = 1;
	for (const auto& digit : baseBRepresentation)
	{
		integer += factor * digit;
		factor *= _base;
	}
	return integer;
}

}
}