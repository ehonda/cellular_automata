#include "gtest/gtest.h"

#include "cell_neighborhood.h"

#include <vector>

#include "cell.h"
#include "k_nearest_neighbors_rule.h"
#include "rule_stub.h"
#include "type_definitions.h"

namespace
{

using namespace cellular_automata;
using namespace integers;

//-----------------------------------------------------------------------------------------------
//TEST FIXTURE CLASS

class CellNeighborhoodTest : public testing::Test
{
protected:
	CellNeighborhoodTest() {}

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

TEST_F(CellNeighborhoodTest, CreationAndEncodingNeighborhoodWork)
{
	//Number 2 = 010 in Base 2
	CellVector cells = { 0, 1, 0 };

	auto cellNeighborhood = CellNeighborhood::createPtr(cells, _rule30);
	auto integerEncodedCellNeighborhood = cellNeighborhood->getIntegerEncodedCellNeighborhood();
	long expectedInteger = 2;
	long actualInteger = integerEncodedCellNeighborhood.getInteger();
	EXPECT_EQ(expectedInteger, actualInteger);
}

TEST_F(CellNeighborhoodTest, ComparisonForEqualityWorks)
{
	CellVector cells = { 1, 1, 0, 0, 1 };
	auto cellNeighborhood = CellNeighborhood::createPtr(cells, _rule30);
	auto otherCellNeighborhood = CellNeighborhood::createPtr(cells, _rule30);
	EXPECT_TRUE(*cellNeighborhood == *otherCellNeighborhood) << "The same cell neighborhoods compare as different.";

	CellVector differentCells = { 1, 1 };
	auto cellNeighborhoodWithDifferentCells = CellNeighborhood::createPtr(differentCells, _rule30);
	EXPECT_FALSE(*cellNeighborhood == *cellNeighborhoodWithDifferentCells)
		<< "Cell neighborhoods with different cells compare as equal";

	state_t base = 3;
	integer_t integer = 33;
	BaseBInteger differentEncodedRule(base, integer);
	integer_t differentNumberOfNeighbors = 5;
	auto differentRule = KNearestNeighborsRule::createPtr(differentEncodedRule, differentNumberOfNeighbors);
	auto cellNeighborhoodWithDifferentRule = CellNeighborhood::createPtr(cells, differentRule);
	EXPECT_FALSE(*cellNeighborhood == *cellNeighborhoodWithDifferentRule)
		<< "Cell neighborhoods with different rules of same type compare as equal";

	state_t numberOfStates = 2;
	RulePtr ruleStub = RuleStub::createPtr(numberOfStates);
	auto cellNeighborhoodWithRuleStub = CellNeighborhood::createPtr(cells, ruleStub);
	EXPECT_FALSE(*cellNeighborhood == *cellNeighborhoodWithRuleStub)
		<< "Cell neighborhoods with different rules of different type compare as equal";
}

//-----------------------------------------------------------------------------------------------

}
