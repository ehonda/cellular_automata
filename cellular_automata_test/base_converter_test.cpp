#include <stdexcept>

#include "gtest/gtest.h"

#include "base_converter.h"
//#include "base_converter.cpp"

namespace
{

using namespace cellular_automata;
using namespace integers;

//-----------------------------------------------------------------------------------------------
//TEST CASES

TEST(BaseConverterTest, RepresentationToIntegerTest)
{
	//Number: 11010 = 26, base2
	int base = 2;
	BaseConverter baseConverter(base);
	BaseConverter::BaseBRepresentation baseBRepresentation = { 0, 1, 0, 1, 1 };
	
	int expectedInteger = 26;
	int convertedInteger = baseConverter.getIntegerFromBaseBRepresentation(baseBRepresentation);
	EXPECT_EQ(expectedInteger, convertedInteger);
}

TEST(BaseConverterTest, IntegerToRepresentationTest)
{
	//Number: 2001 = 55, base3
	int base = 3;
	BaseConverter baseConverter(base);
	BaseConverter::BaseBRepresentation expectedBaseBRepresentation = { 1, 0, 0, 2 };

	int integer = 55;
	auto convertedBaseBRepresentation = baseConverter.getBaseBRepresentationFromInteger(integer);
	EXPECT_EQ(expectedBaseBRepresentation, convertedBaseBRepresentation);
}

TEST(BaseConverterTest, ShouldThrowOnNegativeInteger)
{
	int base = 2;
	BaseConverter baseConverter(base);
	int integer = -10;

	EXPECT_THROW(baseConverter.getBaseBRepresentationFromInteger(integer), std::domain_error);
}

TEST(BaseConverterTest, ShouldThrowOnInvalidBaseBRepresentation)
{
	int base = 2;
	BaseConverter baseConverter(base);
	BaseConverter::BaseBRepresentation representationWithNegativeDigits = { 1, -1 };
	BaseConverter::BaseBRepresentation representationWithTooBigDigits = { 2, 3 };

	EXPECT_THROW(baseConverter.getIntegerFromBaseBRepresentation(representationWithNegativeDigits), std::domain_error);
	EXPECT_THROW(baseConverter.getIntegerFromBaseBRepresentation(representationWithTooBigDigits), std::domain_error);
}

TEST(BaseConverterTest, ShouldThrowOnInvalidBase)
{
	int base = -5;
	EXPECT_THROW(BaseConverter baseConverter(base), std::domain_error);
}

//-----------------------------------------------------------------------------------------------

}
