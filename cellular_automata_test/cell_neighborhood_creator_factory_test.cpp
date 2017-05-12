#include <stdexcept>

#include "gtest/gtest.h"
#include "basic_rules.h"

#include "cell_neighborhood_creator.h"
#include "cell_neighborhood_creator_factory.h"
#include "rule_stub.h"

namespace cellular_automata_test {

using namespace cellular_automata;

class CellNeighborhoodCreatorFactoryTest : public testing::Test {

};

TEST_F(CellNeighborhoodCreatorFactoryTest, test_knn_creator) {
	auto rule30 = BasicRules::getRule30();
	auto creator = CellNeighborhoodCreatorFactory::getCreator(rule30);

	CellVector cells = { 0, 0, 1, 1, 0 };
	auto neighborhood = creator->createCellNeighborhood(
		cells.begin() + 2);
	auto expectedNeighborhood = CellNeighborhood::createPtr(
		{ 0, 1, 1 }, rule30);
	EXPECT_EQ(*neighborhood, *expectedNeighborhood);
}

TEST_F(CellNeighborhoodCreatorFactoryTest, test_throw_on_unkown_rule_subclasses) {
	RulePtr ruleStub = RuleStub::createPtr(2);
	EXPECT_THROW(CellNeighborhoodCreatorFactory::getCreator(ruleStub),
		std::invalid_argument);
}

}
