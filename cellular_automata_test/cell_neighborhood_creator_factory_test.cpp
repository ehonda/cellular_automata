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

TEST_F(CellNeighborhoodCreatorFactoryTest, test_throw_on_unkown_rule_subclasses) {
	RulePtr ruleStub = RuleStub::createPtr(2);
	EXPECT_THROW(CellNeighborhoodCreatorFactory::getCreator(ruleStub, nullptr),
		std::invalid_argument);
}

}
