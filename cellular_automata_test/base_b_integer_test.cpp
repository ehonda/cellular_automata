#include <stdexcept>
#include <vector>

#include "gtest/gtest.h"

#include "base_b_integer.h"
//#include "base_b_integer.cpp"
#include "k_nearest_neighbors_rule.h"

namespace
{

using namespace cellular_automata;
using namespace integers;

//-----------------------------------------------------------------------------------------------
//TEST CASES

TEST(BaseBIntegerTest, DefaultConstructorWorks)
{
	BaseBInteger baseBInteger;

	auto expectedBase = BaseBInteger::DEFAULT_BASE;
	auto actualBase = baseBInteger.getBase();
	EXPECT_EQ(expectedBase, actualBase);

	auto expectedInteger = BaseBInteger::DEFAULT_INTEGER;
	auto actualInteger = baseBInteger.getInteger();
	EXPECT_EQ(expectedInteger, actualInteger);

	auto expectedBaseBRepresentation = BaseBInteger::DEFAULT_BASE_B_REPRESENTATION;
	auto actualBaseBRepresentation = baseBInteger.getBaseBRepresentation();
	EXPECT_EQ(expectedBaseBRepresentation, actualBaseBRepresentation);
}

TEST(BaseBIntegerTest, ConstructFromIntegerWorks)
{
	//Number: 222 = 42 in base 4
	int base = 4;
	int integer = 42;
	BaseBInteger baseBInteger(base, integer);

	BaseBInteger::BaseBRepresentation expectedBaseBRepresentation = { 2, 2, 2 };
	auto convertedBaseBRepresentation = baseBInteger.getBaseBRepresentation();
	EXPECT_EQ(expectedBaseBRepresentation, convertedBaseBRepresentation);
}

TEST(BaseBIntegerTest, ConstructFromBaseBRepresentationWorks)
{
	//Number: 222 = 42 in base 4
	int base = 4;
	BaseBInteger::BaseBRepresentation baseBRepresentation = { 2, 2, 2 };
	BaseBInteger baseBInteger(base, baseBRepresentation);

	int expectedInteger = 42;
	int convertedInteger = baseBInteger.getInteger();
	EXPECT_EQ(expectedInteger, convertedInteger);
}

TEST(BaseBIntegerTest, GetDigitAtWorks)
{
	//Number 111 = 7 in base 2
	int base = 2;
	int integer = 7;
	BaseBInteger baseBInteger(base, integer);

	size_t index = 1;
	int expectedDigit = 1;
	int actualDigit = baseBInteger.getDigitAt(index);
	EXPECT_EQ(expectedDigit, actualDigit);

	index = 3;
	expectedDigit = 0;
	actualDigit = baseBInteger.getDigitAt(index);
	EXPECT_EQ(expectedDigit, actualDigit);
}

TEST(BaseBIntegerTest, ComparisonForEqualityWorks)
{
	//Number 11011 = 27 in base 2
	int base = 2;
	int integer = 27;
	BaseBInteger number27InBase2(base, integer);

	BaseBInteger::BaseBRepresentation base2RepresentationOf27{ 1, 1, 0, 1, 1 };
	BaseBInteger otherNumber27InBase2(base, base2RepresentationOf27);
	EXPECT_EQ(number27InBase2, otherNumber27InBase2);

	//Number 10110 = 22 in base 2
	base = 2;
	integer = 22;
	BaseBInteger number22InBase2(base, integer);
	EXPECT_NE(number27InBase2, number22InBase2) << "Different Integers in the same base compare as equal.";

	//Number 1000 = 27 in base 3
	base = 3;
	integer = 27;
	BaseBInteger number27InBase3(base, integer);
	EXPECT_NE(number27InBase2, number27InBase3) << "The same integers in different bases compare as equal.";
}

TEST(BaseBIntegerTest, ShouldThrowOnConstructionFromInvalidValues)
{
	int invalidBase = 0;
	int validInteger = 100;
	EXPECT_THROW(BaseBInteger baseBInteger(invalidBase, validInteger), std::domain_error);

	int validBase = 2;
	int invalidInteger = -4;
	EXPECT_THROW(BaseBInteger baseBInteger(validBase, invalidInteger), std::domain_error);

	BaseBInteger::BaseBRepresentation invalidBaseBRepresentation = { -1, 0 };
	EXPECT_THROW(BaseBInteger baseBInteger(validBase, invalidBaseBRepresentation), std::domain_error);
}

//-----------------------------------------------------------------------------------------------

}
