#include <vector>

#include "gtest/gtest.h"

#include "base_converter.h"
#include "base_converter.cpp"

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

//-----------------------------------------------------------------------------------------------

}