#include "gtest/gtest.h"

#include "k_nearest_neighbors_cell_neighborhood_creator.h"
#include "k_nearest_neighbors_cell_neighborhood_creator.cpp"

namespace
{

using namespace cellular_automata;
using namespace integers;

//-----------------------------------------------------------------------------------------------
//TEST FIXTURE CLASS

class KNearestNeighborsCellNeighborhoodCreatorTest : public testing::Test
{
protected:
	KNearestNeighborsCellNeighborhoodCreatorTest() {}

	virtual void SetUp()
	{
		_someBase10RuleEncoded = BaseBInteger(10, 111);
		_baseCells = CellVector{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	}

	virtual KNearestNeighborsCellNeighborhood* getRawKNearestNeighborsCellNeighborhoodPtr(
		const CellNeighborhoodPtr& cellNeighborhoodPtr)
	{
		return dynamic_cast<KNearestNeighborsCellNeighborhood*>(cellNeighborhoodPtr.get());
	}

	BaseBInteger _someBase10RuleEncoded;
	CellVector _baseCells;
};

//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
//TEST CASES

TEST_F(KNearestNeighborsCellNeighborhoodCreatorTest, EvenNumberOfNeighborsWorks)
{
	integer_t numberOfNeighbors = 4;
	auto rule = KNearestNeighborsRule::createPtr(_someBase10RuleEncoded, numberOfNeighbors);
	KNearestNeighborsCellNeighborhoodCreator creator(rule);

	CellVector expectedCellsInNeighborhood{ 2, 3, 4, 5 };
	auto expectedCellNeighborhood = KNearestNeighborsCellNeighborhood::createPtr(expectedCellsInNeighborhood, rule);

	auto center = _baseCells.begin() + 4;
	auto actualCellNeighborhood = creator.createCellNeighborhood(center);

	EXPECT_EQ(*expectedCellNeighborhood, *getRawKNearestNeighborsCellNeighborhoodPtr(actualCellNeighborhood));
}

TEST_F(KNearestNeighborsCellNeighborhoodCreatorTest, OddNumberOfNeighborsWorks)
{
	integer_t numberOfNeighbors = 5;
	auto rule = KNearestNeighborsRule::createPtr(_someBase10RuleEncoded, numberOfNeighbors);
	KNearestNeighborsCellNeighborhoodCreator creator(rule);

	CellVector expectedCellsInNeighborhood{ 2, 3, 4, 5, 6 };
	auto expectedCellNeighborhood = KNearestNeighborsCellNeighborhood::createPtr(expectedCellsInNeighborhood, rule);

	auto center = _baseCells.begin() + 4;
	auto actualCellNeighborhood = creator.createCellNeighborhood(center);

	EXPECT_EQ(*expectedCellNeighborhood, *getRawKNearestNeighborsCellNeighborhoodPtr(actualCellNeighborhood));
}

//-----------------------------------------------------------------------------------------------

}