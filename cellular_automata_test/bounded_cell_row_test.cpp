#include "gtest/gtest.h"

#include "bounded_cell_row.h"
#include "bounded_cell_row.cpp"

#include "cell.h"
#include "cell_neighborhood_creator.h"
#include "k_nearest_neighbors_rule.h"
#include "k_nearest_neighbors_cell_neighborhood_creator.h"
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
	BoundedCellRowTest() {}

	virtual void SetUp()
	{
		BaseBInteger someBase10RuleEncoded(10, 111);
		integer_t numberOfNeighbors = 3;
		_knnRule = KNearestNeighborsRule::createPtr(someBase10RuleEncoded, numberOfNeighbors);
		_baseCells = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	}

	virtual CellNeighborhoodCreatorPtr getKnnNeighborhoodCreator() const noexcept
	{
		return std::make_unique<KNearestNeighborsCellNeighborhoodCreator>(_knnRule);
	}

	KNearestNeighborsRulePtr _knnRule;
	CellVector _baseCells;
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

TEST_F(BoundedCellRowTest, SettingBoundaryCellWorks)
{
	BoundedCellRow boundedCellRow(getKnnNeighborhoodCreator(), _baseCells);
	Cell boundaryCell(5);
	boundedCellRow.setBoundaryCell(boundaryCell);

	CellVector expectedCells = { 5, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 5 };
	auto actualCells = boundedCellRow.getCellsIncludingBoundaries();
	EXPECT_EQ(expectedCells, actualCells);
}

//-----------------------------------------------------------------------------------------------

}
