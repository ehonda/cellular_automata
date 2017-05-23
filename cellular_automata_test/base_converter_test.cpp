#include <stdexcept>

#include "gtest/gtest.h"
#include "gtest_mpz_utils.h"
#include "base_b_integers_testing_utils.h"

#include "base_converter.h"
#include "cell.h"

using namespace cellular_automata;
using namespace integers;

namespace cellular_automata_test {

class BaseConverterTest : public testing::Test {
protected:
	BaseConverterTest() 
		: baseConverter_(2) {
	}

	//################################################################
	// Domain specific language

	void makeBaseConverterForBase(long base) {
		baseConverter_ = BaseConverter(base);
	}

	void expectBigEndianRepresentationFromInteger(const mpz_class& integer, const std::string& bigEndianRep) const {
		auto expectedLittleEndianRep = convertToLittleEndian(bigEndianRep);
		auto littleEndianRep = baseConverter_.getBaseBRepresentationFromInteger(integer);
		EXPECT_EQ(littleEndianRep, expectedLittleEndianRep);
	}

	void expectBigEndianRepresentationFromInteger(long integer, const std::string& bigEndianRep) const {
		auto expectedLittleEndianRep = convertToLittleEndian(bigEndianRep);
		auto littleEndianRep = baseConverter_.getBaseBRepresentationFromInteger(integer);
		EXPECT_EQ(littleEndianRep, expectedLittleEndianRep);
	}

	void expectIntegerFromBigEndianRepresentation(const std::string& bigEndianRep, long expectedInteger) const {
		auto littleEndianRep = convertToLittleEndian(bigEndianRep);
		auto integer = baseConverter_.getIntegerFromBaseBRepresentation(littleEndianRep);
		EXPECT_EQ(integer, expectedInteger);
	}

	void expectIntegerFromBigEndianCellNeighborhood(const std::string& bigEndianRep, long expectedInteger) const {
		auto littleEndianRep = convertToLittleEndian(bigEndianRep);
		auto littleEndianCellNeighborhood = convertToCellNeighborhood(littleEndianRep);
		long integer = baseConverter_.getIntegerFromCellNeighborhood(littleEndianCellNeighborhood);
		EXPECT_EQ(integer, expectedInteger);
	}

	void expectIntegerFromBigEndianRepresentation(const std::string& bigEndianRep, const mpz_class& expectedInteger) const {
		auto littleEndianRep = convertToLittleEndian(bigEndianRep);
		auto integer = baseConverter_.getMpzFromBaseBRepresentation(littleEndianRep);
		EXPECT_EQ_MPZ(integer, expectedInteger);
	}

	// End Domain specific language
	//################################################################

	std::vector<Cell> convertToCellNeighborhood(const BaseConverter::BaseBRepresentation& baseBRep) const {
		std::vector<Cell> cellNeighborhood;
		for (const auto& state : baseBRep)
			cellNeighborhood.emplace_back(state);
		return cellNeighborhood;
	}

	BaseConverter baseConverter_;
};

//-----------------------------------------------------------------------------------------------
//TEST CASES

TEST_F(BaseConverterTest, get_representation_from_long) {
	//55 ~ 2001 in base 3
	makeBaseConverterForBase(3);
	expectBigEndianRepresentationFromInteger(55, "2001");
}

TEST_F(BaseConverterTest, get_representation_from_mpz_class) {
	//42 ~ 101010 in base 2
	makeBaseConverterForBase(2);
	//expectBigEndianRepresentationFromInteger(mpz_class(42), { 1, 0, 1, 0, 1, 0 });
	expectBigEndianRepresentationFromInteger(mpz_class(42), "101010");
}

TEST_F(BaseConverterTest, get_integer_from_representation) {
	//26 ~ 11010 in base 2
	makeBaseConverterForBase(2);
	expectIntegerFromBigEndianRepresentation("11010", 26);
}

TEST_F(BaseConverterTest, get_integer_from_cell_neighborhood) {
	//6 ~ 110 in base 2
	makeBaseConverterForBase(2);
	expectIntegerFromBigEndianCellNeighborhood("110", 6);
}

TEST_F(BaseConverterTest, get_mpz_class_from_representation) {
	//100 ~ 400 in base 5
	makeBaseConverterForBase(5);
	expectIntegerFromBigEndianRepresentation("400", mpz_class(100));
}

TEST_F(BaseConverterTest, ShouldThrowOnNegativeInteger)
{
	int base = 2;
	BaseConverter baseConverter(base);
	int integer = -10;

	EXPECT_THROW(baseConverter.getBaseBRepresentationFromInteger(integer), std::domain_error);
}

TEST_F(BaseConverterTest, ShouldThrowOnInvalidBaseBRepresentation)
{
	int base = 2;
	BaseConverter baseConverter(base);
	BaseConverter::BaseBRepresentation representationWithNegativeDigits = { 1, -1 };
	BaseConverter::BaseBRepresentation representationWithTooBigDigits = { 2, 3 };

	EXPECT_THROW(baseConverter.getIntegerFromBaseBRepresentation(representationWithNegativeDigits), std::domain_error);
	EXPECT_THROW(baseConverter.getIntegerFromBaseBRepresentation(representationWithTooBigDigits), std::domain_error);
}

TEST_F(BaseConverterTest, ShouldThrowOnInvalidBase)
{
	int base = -5;
	EXPECT_THROW(BaseConverter baseConverter(base), std::domain_error);
}

//-----------------------------------------------------------------------------------------------

}
