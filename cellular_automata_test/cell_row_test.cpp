#include <stdexcept>

#include "gtest/gtest.h"

#include "cell_row.h"
#include "cell_row.cpp"

#include "cell_row_stub.h"
#include "cell_row_stub.cpp"
#include "cell_neighborhood_creator.h"
#include "k_nearest_neighbors_cell_neighborhood_creator.h"
#include "k_nearest_neighbors_rule.h"
#include "type_definitions.h"

namespace
{

using namespace cellular_automata;
using namespace integers;

//-----------------------------------------------------------------------------------------------
//TEST FIXTURE CLASS

class CellRowTest : public testing::Test
{
protected:
	virtual void SetUp()
	{
		BaseBInteger someBase10RuleEncoded(10, 111);
		integer_t numberOfNeighbors = 3;
		_knnRule = KNearestNeighborsRule::createPtr(someBase10RuleEncoded, numberOfNeighbors);

		integer_t differentNumberOfNeighbors = 5;
		_differentKnnRule = KNearestNeighborsRule::createPtr(someBase10RuleEncoded, differentNumberOfNeighbors);

		_baseCells = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		_differentBaseCells = { 0, 1 };
	}

	virtual CellNeighborhoodCreatorPtr getKnnNeighborhoodCreator() const noexcept
	{
		return std::make_unique<KNearestNeighborsCellNeighborhoodCreator>(_knnRule);
	}

	virtual CellNeighborhoodCreatorPtr getDifferentKnnNeighborhoodCreator() const noexcept
	{
		return std::make_unique<KNearestNeighborsCellNeighborhoodCreator>(_differentKnnRule);
	}

	KNearestNeighborsRulePtr _knnRule;
	KNearestNeighborsRulePtr _differentKnnRule;
	CellVector _baseCells;
	CellVector _differentBaseCells;
};

//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
//TEST CASES

TEST_F(CellRowTest, ConstructionAndGettingNeighborhoodWork)
{
	auto knnNeighborhoodCreator = getKnnNeighborhoodCreator();
	CellRowStub cellRow(knnNeighborhoodCreator);

	CellVector expectedCells{ 6, 7, 8 };
	auto expectedNeighborhood = CellNeighborhood::createPtr(expectedCells, _knnRule);
	
	auto center = _baseCells.cbegin() + 7;
	auto actualNeighborhood = cellRow.getNeighborhood(center);
	EXPECT_EQ(*expectedNeighborhood, *actualNeighborhood);
}

TEST_F(CellRowTest, ShouldThrowWhenConstructedWithNullPtr)
{
	CellNeighborhoodCreatorPtr null(nullptr);
	EXPECT_THROW(CellRowStub cellRow(null), std::invalid_argument);
}

TEST_F(CellRowTest, ComparisonForEqualityWorks)
{
	auto knnNeighborhoodCreator = getKnnNeighborhoodCreator();
	auto sameKnnNeighborhoodCreator = getKnnNeighborhoodCreator();
	CellRowStub cellRow(knnNeighborhoodCreator);
	CellRowStub sameCellRow(sameKnnNeighborhoodCreator);
	EXPECT_EQ(cellRow, sameCellRow);

	auto differentKnnNeighborhoodCreator = getDifferentKnnNeighborhoodCreator();
	CellRowStub differentCellRow(differentKnnNeighborhoodCreator);
	EXPECT_NE(cellRow, differentCellRow);
}

//-----------------------------------------------------------------------------------------------

}
