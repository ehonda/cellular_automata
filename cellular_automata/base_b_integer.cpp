#include "base_b_integer.h"

#include "base_converter.h"

namespace cellular_automata
{
namespace integers
{

BaseBInteger::BaseBInteger(long base, long integer)
	: _base(base), _integer(integer)
{
	BaseConverter baseConverter(base);
	_baseBRepresentation = baseConverter.getBaseBRepresentationFromInteger(integer);
}

BaseBInteger::BaseBInteger(long base, const BaseBRepresentation& baseBRepresentation)
	: _base(base), _baseBRepresentation(baseBRepresentation)
{
	BaseConverter baseConverter(base);
	_integer = baseConverter.getIntegerFromBaseBRepresentation(baseBRepresentation);
}

long BaseBInteger::getInteger() const noexcept
{
	return _integer;
}

const BaseBInteger::BaseBRepresentation& BaseBInteger::getBaseBRepresentation() const noexcept
{
	return _baseBRepresentation;
}

long BaseBInteger::getDigitAt(size_t index) const
{
	if (index >= _baseBRepresentation.size())
		return 0;
	else
		return _baseBRepresentation[index];
}

long BaseBInteger::getBase() const noexcept
{
	return _base;
}

bool BaseBInteger::operator==(const BaseBInteger& other) const noexcept
{
	return (_base == other._base) && (_integer == other._integer);
}

}
}
