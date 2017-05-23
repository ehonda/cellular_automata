#include "base_b_integer.h"

#include "base_converter.h"
#include "cell.h"

namespace cellular_automata {
namespace integers {

const mpz_class BaseBInteger::DEFAULT_MPZ(0);
const BaseBInteger::BaseBRepresentation BaseBInteger::DEFAULT_BASE_B_REPRESENTATION{ 0 };

BaseBInteger::BaseBInteger()
	: _base(DEFAULT_BASE), integer_(DEFAULT_MPZ), _baseBRepresentation(DEFAULT_BASE_B_REPRESENTATION)
{
}

BaseBInteger::BaseBInteger(long base, const mpz_class& integer)
	: _base(base), integer_(integer) {
	BaseConverter baseConverter(_base);
	_baseBRepresentation = baseConverter.getBaseBRepresentationFromInteger(integer_);
}

BaseBInteger::BaseBInteger(long base, const BaseBRepresentation& baseBRepresentation)
	: _base(base), _baseBRepresentation(baseBRepresentation)
{
	BaseConverter baseConverter(base);
	integer_ = baseConverter.getMpzFromBaseBRepresentation(baseBRepresentation);
}

long BaseBInteger::getBase() const noexcept
{
	return _base;
}

const mpz_class& BaseBInteger::getInteger() const noexcept {
	return integer_;
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
	return (_base == other._base) && (integer_ == other.integer_);
}

bool BaseBInteger::operator!=(const BaseBInteger& other) const noexcept
{
	return !operator==(other);
}

}
}
