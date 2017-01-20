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

TEST(CellRowTest, ConstructionAndGettingNeighborhoodWork)
{
	BaseBInteger someBase10RuleEncoded(10, 444);
	integer_t numberOfNeighbors = 3;
	auto knnRule = KNearestNeighborsRule::createPtr(someBase10RuleEncoded, numberOfNeighbors);
	CellNeighborhoodCreatorPtr knnNeighborhoodCreator = std::make_unique<KNearestNeighborsCellNeighborhoodCreator>(knnRule);
	
	CellRowStub cellRow(knnNeighborhoodCreator);
	CellVector baseCells{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	auto center = baseCells.cbegin() + 7;

	CellVector expectedCells{ 6, 7, 8 };
	auto expectedNeighborhood = CellNeighborhood::createPtr(expectedCells, knnRule);
	
	auto actualNeighborhood = cellRow.getNeighborhood(center);
	EXPECT_EQ(*expectedNeighborhood, *actualNeighborhood);
}

}
