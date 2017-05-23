#include <stdexcept>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "gtest_mpz_utils.h"
#include "base_b_integers_testing_utils.h"

#include "base_b_integer.h"

using namespace cellular_automata;
using namespace integers;

namespace cellular_automata_test {

class BaseBIntegerTest : public testing::Test {
protected:
	//################################################################
	// Domain specific language

	void expectBase(long expectedBase) const {
		long base = baseBInteger_.getBase();
		EXPECT_EQ(base, expectedBase);
	}

	void expectMpz(mpz_class expectedMpz) const {
		mpz_class mpz = baseBInteger_.getInteger();
		EXPECT_EQ_MPZ(mpz, expectedMpz);
	}

	void expectBigEndianRepresentation(const std::string& bigEndianRep) const {
		auto expectedLittleEndianRep = convertToLittleEndian(bigEndianRep);
		auto littleEndianRep = baseBInteger_.getBaseBRepresentation();
		EXPECT_EQ(littleEndianRep, expectedLittleEndianRep);
	}

	// End Domain specific language
	//################################################################

	BaseBInteger baseBInteger_;
};

//-----------------------------------------------------------------------------------------------
//TEST CASES

TEST_F(BaseBIntegerTest, construct_from_mpz_class) {
	//1100 ~ 12 in base 2
	baseBInteger_ = BaseBInteger(2, mpz_class(12));
	expectBase(2);
	expectMpz(12);
	expectBigEndianRepresentation("1100");
}

TEST_F(BaseBIntegerTest, construct_from_base_b_representation)
{
	//222 ~ 42 in base 4
	baseBInteger_ = BaseBInteger(4, { 2, 2, 2 });
	expectBase(4);
	expectMpz(42);
	expectBigEndianRepresentation("222");
}

TEST_F(BaseBIntegerTest, DefaultConstructorWorks)
{
	BaseBInteger baseBInteger;

	auto expectedBase = BaseBInteger::DEFAULT_BASE;
	auto actualBase = baseBInteger.getBase();
	EXPECT_EQ(expectedBase, actualBase);

	mpz_class expectedMpz = BaseBInteger::DEFAULT_MPZ;
	mpz_class actualMpz = baseBInteger.getInteger();
	EXPECT_EQ_MPZ(actualMpz, expectedMpz);

	auto expectedBaseBRepresentation = BaseBInteger::DEFAULT_BASE_B_REPRESENTATION;
	auto actualBaseBRepresentation = baseBInteger.getBaseBRepresentation();
	EXPECT_EQ(expectedBaseBRepresentation, actualBaseBRepresentation);
}

TEST_F(BaseBIntegerTest, GetDigitAtWorks)
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

TEST_F(BaseBIntegerTest, ComparisonForEqualityWorks)
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

TEST_F(BaseBIntegerTest, ShouldThrowOnConstructionFromInvalidValues)
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
