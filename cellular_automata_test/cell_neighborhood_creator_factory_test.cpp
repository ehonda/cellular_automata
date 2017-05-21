#include <stdexcept>

#include "gtest/gtest.h"
#include "basic_rules.h"

#include "cell_neighborhood_creator.h"
#include "cell_neighborhood_creator_factory.h"
#include "cell_row.h"
#include "rule_stub.h"

namespace cellular_automata_test {

using namespace cellular_automata;

class CellNeighborhoodCreatorFactoryTest : public testing::Test {
protected:
	RulePtr rule_ = BasicRules::getSierpinskiRule();
	CellRow row_;
};

typedef CellNeighborhoodCreatorFactoryTest CellNeighborhoodCreatorFactoryDeathTest;

TEST_F(CellNeighborhoodCreatorFactoryTest, throws_on_nullptr_rule) {
	EXPECT_THROW(CellNeighborhoodCreatorFactory::getCreator(RulePtr(), &row_),
		std::invalid_argument);
}

TEST_F(CellNeighborhoodCreatorFactoryTest, throws_on_nullptr_cell_row) {
	EXPECT_THROW(CellNeighborhoodCreatorFactory::getCreator(rule_, nullptr),
		std::invalid_argument);
}

TEST_F(CellNeighborhoodCreatorFactoryDeathTest, dies_on_unkown_rule_subclass) {
	RulePtr unkownRuleSubclass = RuleStub::createPtr(2);
	EXPECT_DEATH(CellNeighborhoodCreatorFactory::getCreator(unkownRuleSubclass, &row_),
		"Unkown rule subclass can not be used to instantiate CellNeighborhoodCreator.");
}

}
