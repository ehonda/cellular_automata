#include "gtest/gtest.h"

#include "k_nearest_neighbors_cell_neighborhood.h"
#include "k_nearest_neighbors_cell_neighborhood.cpp"

#include <vector>

#include "cell.h"
#include "cell_neighborhood.h"
#include "cell_neighborhood.cpp"
#include "k_nearest_neighbors_rule.h"
#include "type_definitions.h"

using namespace cellular_automata;
using namespace integers;

namespace {

//-----------------------------------------------------------------------------------------------
//TEST FIXTURE CLASS

class KNearestNeighborsCellNeighborhoodTest : public testing::Test
{
protected:
	KNearestNeighborsCellNeighborhoodTest() {}

	virtual void SetUp()
	{
		BaseBInteger rule30Encoded(2, 30);
		_rule30 = KNearestNeighborsRule::createPtr(rule30Encoded, 3);
	}

	KNearestNeighborsRulePtr _rule30;
};

//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
//TEST CASES

TEST_F(KNearestNeighborsCellNeighborhoodTest, CreationAndEncodingNeighborhoodWork)
{
	//Number 2 = 010 in Base 2
	CellVector cells = { 0, 1, 0 };

	auto cellNeighborhood = KNearestNeighborsCellNeighborhood::createPtr(cells, _rule30);
	auto integerEncodedCellNeighborhood = cellNeighborhood->getIntegerEncodedCellNeighborhood();
	long expectedInteger = 2;
	long actualInteger = integerEncodedCellNeighborhood.getInteger();
	EXPECT_EQ(expectedInteger, actualInteger);
}

TEST_F(KNearestNeighborsCellNeighborhoodTest, ComparisonForEqualityWorks)
{
	CellVector cells = { 1, 1, 0, 0, 1 };
	auto cellNeighborhood = KNearestNeighborsCellNeighborhood::createPtr(cells, _rule30);
	auto otherCellNeighborhood = KNearestNeighborsCellNeighborhood::createPtr(cells, _rule30);
	EXPECT_TRUE(*cellNeighborhood == *otherCellNeighborhood) << "The same cell neighborhoods compare as different.";

	CellVector differentCells = { 1, 1 };
	auto cellNeighborhoodWithDifferentCells = KNearestNeighborsCellNeighborhood::createPtr(differentCells, _rule30);
	EXPECT_FALSE(*cellNeighborhood == *cellNeighborhoodWithDifferentCells)
		<< "Cell neighborhoods with different cells compare as equal";

	int base = 3;
	int integer = 33;
	BaseBInteger differentEncodedRule(base, integer);
	int differentNumberOfNeighbors = 5;
	auto differentRule = KNearestNeighborsRule::createPtr(differentEncodedRule, differentNumberOfNeighbors);
	auto cellNeighborhoodWithDifferentRule = KNearestNeighborsCellNeighborhood::createPtr(cells, differentRule);
	EXPECT_FALSE(*cellNeighborhood == *cellNeighborhoodWithDifferentRule)
		<< "Cell neighborhoods with different rules compare as equal";
}

//-----------------------------------------------------------------------------------------------

}