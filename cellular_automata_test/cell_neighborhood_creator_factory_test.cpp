#include "gtest/gtest.h"
#include "basic_rules.h"

#include "cell_neighborhood_creator_factory.h"


namespace cellular_automata_test {

using namespace cellular_automata;

class CellNeighborhoodCreatorFactoryTest : public testing::Test {

};

TEST_F(CellNeighborhoodCreatorFactoryTest, test_knn_creator) {
	CellNeighborhoodCreatorFactory factory;
	auto rule30 = BasicRules::getRule30();
	//auto creator = CellNeighborhoodCreatorFactory::getCreator(rule30);
}

}
