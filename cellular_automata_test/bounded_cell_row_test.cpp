#include "gtest/gtest.h"

#include "bounded_cell_row.h"
//#include "bounded_cell_row.cpp"

#include "cell.h"
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

class BoundedCellRowTest : public testing::Test
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

TEST_F(BoundedCellRowTest, ConstructionWorks)
{
	BoundedCellRow boundedCellRow(getKnnNeighborhoodCreator(), _baseCells);
	CellVector expectedCells = { 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	auto actualCells = boundedCellRow.getCellsIncludingBoundaries();
	EXPECT_EQ(expectedCells, actualCells);
}

TEST_F(BoundedCellRowTest, SetBoundaryCellWorks)
{
	BoundedCellRow boundedCellRow(getKnnNeighborhoodCreator(), _baseCells);
	Cell boundaryCell(5);
	boundedCellRow.setBoundaryCell(boundaryCell);

	CellVector expectedCells = { 5, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 5 };
	auto actualCells = boundedCellRow.getCellsIncludingBoundaries();
	EXPECT_EQ(expectedCells, actualCells);
}

TEST_F(BoundedCellRowTest, GettingIteratorsWorks)
{
	BoundedCellRow boundedCellRow(getKnnNeighborhoodCreator(), _baseCells);
	Cell boundaryCell(5);
	boundedCellRow.setBoundaryCell(boundaryCell);
	const auto& cells = boundedCellRow.getCellsIncludingBoundaries();

	auto cbegin = boundedCellRow.cbegin();
	EXPECT_EQ(*cbegin, Cell(0));
	EXPECT_EQ(--cbegin, cells.cbegin());

	auto cend = boundedCellRow.cend();
	EXPECT_EQ(*cend, boundaryCell);
	EXPECT_EQ(++cend, cells.cend());
}

TEST_F(BoundedCellRowTest, ComparisonForEqualityWorks)
{
	BoundedCellRow boundedCellRow(getKnnNeighborhoodCreator(), _baseCells);
	BoundedCellRow sameBoundedCellRow(getKnnNeighborhoodCreator(), _baseCells);
	EXPECT_EQ(boundedCellRow, sameBoundedCellRow);

	BoundedCellRow boundedCellRowWithDifferentRule(getDifferentKnnNeighborhoodCreator(), _baseCells);
	EXPECT_NE(boundedCellRow, boundedCellRowWithDifferentRule);

	BoundedCellRow boundedCellRowWithDifferentBaseCells(getKnnNeighborhoodCreator(), _differentBaseCells);
	EXPECT_NE(boundedCellRow, boundedCellRowWithDifferentBaseCells);
}

TEST_F(BoundedCellRowTest, GetPtrToCopyWorks)
{
	std::unique_ptr<BoundedCellRow> boundedCellRowPtr
		= std::make_unique<BoundedCellRow>(getKnnNeighborhoodCreator(), _baseCells);
	auto boundedCellRowCopyPtr = boundedCellRowPtr->getPtrToCopy();
	EXPECT_EQ(*boundedCellRowPtr, *boundedCellRowCopyPtr);
}

//-----------------------------------------------------------------------------------------------

}
