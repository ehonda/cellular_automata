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
	auto knnNeighborhoodCreator = std::make_unique<KNearestNeighborsCellNeighborhoodCreator>(knnRule);

	//CellRowStub cellRow(knnNeighborhoodCreator);
}

}