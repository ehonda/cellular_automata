#include "base_b_integer.h"

#include "base_converter.h"
#include "cell.h"

namespace cellular_automata
{
namespace integers
{

const BaseBInteger::BaseBRepresentation BaseBInteger::DEFAULT_BASE_B_REPRESENTATION{ 0 };

BaseBInteger::BaseBInteger()
	: _base(DEFAULT_BASE), _integer(DEFAULT_INTEGER), _baseBRepresentation(DEFAULT_BASE_B_REPRESENTATION)
{
}

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

BaseBInteger::BaseBInteger(long base, const CellVector& cells) 
	: _base(base) {
	for (const auto& cell : cells)
		_baseBRepresentation.emplace_back(cell.getState());
	BaseConverter baseConverter(base);
	_integer = baseConverter.getIntegerFromBaseBRepresentation(_baseBRepresentation);
}

long BaseBInteger::getBase() const noexcept
{
	return _base;
}

long BaseBInteger::getInteger() const noexcept
{
	return _integer;
}

const BaseBInteger::BaseBRepresentation& BaseBInteger::getBaseBRepresentation() const noexcept
{
	return _baseBRepresentation;
}

long BaseBInteger::getDigitAt(size_t index) const noexcept
{
	if (index >= _baseBRepresentation.size())
		return 0;
	else
		return _baseBRepresentation[index];
}

bool BaseBInteger::operator==(const BaseBInteger& other) const noexcept
{
	return (_base == other._base) && (_integer == other._integer);
}

bool BaseBInteger::operator!=(const BaseBInteger& other) const noexcept
{
	return !operator==(other);
}

}
}
