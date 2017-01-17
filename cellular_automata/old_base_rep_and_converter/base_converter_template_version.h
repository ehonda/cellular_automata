#pragma once

#include <vector>

template<typename IntegerType, typename BaseType = IntegerType>
class BaseConverter
{
public:
	typedef typename std::vector<BaseType> BaseBRepresentationType;

	BaseConverter(const BaseType& base);
	
	BaseBRepresentationType getBaseBRepresentationFromInteger(const IntegerType& integer) const;
	IntegerType getIntegerFromBaseBRepresentation(const BaseBRepresentationType& baseBRepresentation) const;

private:
	BaseType _base;
};

template<typename IntegerType, typename BaseType = IntegerType>
inline BaseConverter<IntegerType, BaseType>::BaseConverter(const BaseType& base)
	: _base(base)
{
}

template<typename IntegerType, typename BaseType = IntegerType>
typename BaseConverter<IntegerType, BaseType>::BaseBRepresentationType
inline BaseConverter<IntegerType, BaseType>::getBaseBRepresentationFromInteger(const IntegerType& integer) const
{
	BaseBRepresentationType baseBRepresentation;
	IntegerType remainder;
	IntegerType integerCopy(integer);
	while (integerCopy != 0)
	{
		remainder = integerCopy % _base;
		integerCopy -= remainder;
		integerCopy /= _base;
		baseBRepresentation.emplace_back(remainder);
	}
	return baseBRepresentation;
}

template<typename IntegerType, typename BaseType = IntegerType>
inline IntegerType BaseConverter<IntegerType, BaseType>::getIntegerFromBaseBRepresentation(const BaseBRepresentationType& baseBRepresentation) const
{
	IntegerType integer = 0;
	IntegerType factor = 1;
	for (const auto& digit : baseBRepresentation)
	{
		integer += factor * digit;
		factor *= _base;
	}
	return integer;
}