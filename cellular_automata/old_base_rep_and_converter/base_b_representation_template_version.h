#pragma once

#include <string>
#include <vector>

#include "base_converter.h"

template<typename IntegerType, typename BaseType = IntegerType>
class BaseBRepresentation
{
public:
	typedef typename std::vector<BaseType> BaseBRepresentationType;

	BaseBRepresentation() = default;
	BaseBRepresentation(const BaseType& base, const IntegerType& integer);
	BaseBRepresentation(const BaseType& base, const BaseBRepresentationType& baseBRepresentation);

	const IntegerType& getInteger() const noexcept;
	const BaseBRepresentationType& getBaseBRepresentation() const noexcept;

	std::string print() const noexcept;

private:
	BaseType _base;
	IntegerType _integer;
	BaseBRepresentationType _baseBRepresentation;
};

template<typename IntegerType, typename BaseType = IntegerType>
inline BaseBRepresentation<IntegerType, BaseType>::BaseBRepresentation(const BaseType& base, const IntegerType& integer)
	: _base(base), _integer(integer)
{
	BaseConverter<IntegerType, BaseType> baseConverter(base);
	_baseBRepresentation = baseConverter.getBaseBRepresentationFromInteger(integer);
}

template<typename IntegerType, typename BaseType = IntegerType>
inline BaseBRepresentation<IntegerType, BaseType>::BaseBRepresentation(const BaseType& base, const BaseBRepresentationType& baseBRepresentation)
	: _base(base), _baseBRepresentation(baseBRepresentation)
{
	BaseConverter<IntegerType, BaseType> baseConverter(base);
	_integer = baseConverter.getIntegerFromBaseBRepresentation(baseBRepresentation);
}

template<typename IntegerType, typename BaseType>
inline const IntegerType& BaseBRepresentation<IntegerType, BaseType>::getInteger() const noexcept
{
	// TODO: insert return statement here
}

template<typename IntegerType, typename BaseType>
inline const BaseBRepresentation<IntegerType, BaseType>::BaseBRepresentationType& BaseBRepresentation<IntegerType, BaseType>::getBaseBRepresentation() const noexcept
{
	// TODO: insert return statement here
}

template<typename IntegerType, typename BaseType = IntegerType>
inline std::string BaseBRepresentation<IntegerType, BaseType>::print() const noexcept
{
	std::string stringRepresentation;
	for (auto it = _baseBRepresentation.crbegin(); it != _baseBRepresentation.crend(); ++it)
		stringRepresentation.append(std::to_string(*it));
	return stringRepresentation;
}