#include <memory>
#include <stdexcept>

#include "gtest/gtest.h"
#include "basic_rules.h"

#include "k_nearest_neighbors_rule.h"

#include "base_b_integer.h"
#include "type_definitions.h"

using namespace cellular_automata;
using namespace integers;

namespace cellular_automata_test {

class KNearestNeighborsRuleTest : public testing::Test {
protected:
};

TEST_F(KNearestNeighborsRuleTest, test_get_random_rule_of_same_type) {
	int states = 3;
	int neighbors = 3;
	auto rule = BasicRules::getKnnRule(states, 0, neighbors);
	auto randomRule = rule->getRandomRuleOfSameType();

	auto knnRandomRule = std::dynamic_pointer_cast<KNearestNeighborsRule, Rule>(randomRule);
	ASSERT_TRUE(knnRandomRule) << "Random rule could not be cast to KNearestNeighborsRule";
	EXPECT_EQ(knnRandomRule->getNumberOfStates(), states);
	EXPECT_EQ(knnRandomRule->getNumberOfNeighbors(), neighbors);
	EXPECT_NE(*rule, *knnRandomRule) << "Probabilistic test with very low probability failed";
}

TEST_F(KNearestNeighborsRuleTest, test_get_next_gen_for_center_cell) {
	auto rule = BasicRules::getSierpinskiRule();
	CellVector neighborhood = { 0, 0, 1 };
	Cell nextGen = rule->getNextGenerationForCenterCell(neighborhood);
	Cell expectedNextGen(1);
	EXPECT_EQ(nextGen, expectedNextGen);
}

TEST_F(KNearestNeighborsRuleTest, CreationWorks)
{
	state_t expectedNumberOfStates = 4;
	BaseBInteger integerEncodedRule(expectedNumberOfStates, 56);
	integer_t expectedNumberOfNeighbors = 7;
	auto rule = KNearestNeighborsRule::createPtr(integerEncodedRule, expectedNumberOfNeighbors);

	state_t actualNumberOfStates = rule->getNumberOfStates();
	integer_t actualNumberOfNeighbors = rule->getNumberOfNeighbors();
	EXPECT_EQ(actualNumberOfStates, expectedNumberOfStates);
	EXPECT_EQ(actualNumberOfNeighbors, expectedNumberOfNeighbors);
}

TEST_F(KNearestNeighborsRuleTest, GettingNextGenerationWOrks)
{
	BaseBInteger rule110Encoded(2, 110);
	auto rule110 = KNearestNeighborsRule::createPtr(rule110Encoded, 3);

	CellVector cells = { 1, 1, 1 };
	CellNeighborhoodPtr cellNeighborhood = CellNeighborhood::createPtr(cells, rule110);

	Cell expectedCell(0);
	Cell actualCell = rule110->getNextGeneration(cellNeighborhood);
	EXPECT_EQ(actualCell.getState(), expectedCell.getState());
}

TEST_F(KNearestNeighborsRuleTest, ComparisonForEqualityWorks)
{
	BaseBInteger rule110Encoded(2, 110);
	integer_t numberOfNeighbors = 3;
	auto rule110 = KNearestNeighborsRule::createPtr(rule110Encoded, numberOfNeighbors);
	auto otherRule110 = KNearestNeighborsRule::createPtr(rule110Encoded, numberOfNeighbors);
	EXPECT_TRUE(*rule110 == *otherRule110) << "The same rules compare as different.";

	BaseBInteger rule30Encoded(2, 30);
	auto rule30 = KNearestNeighborsRule::createPtr(rule30Encoded, numberOfNeighbors);
	EXPECT_FALSE(*rule110 == *rule30) << "Different rule encodings with same number of Neighbors compare as equal.";

	numberOfNeighbors = 5;
	auto rule110With5Neighbors = KNearestNeighborsRule::createPtr(rule110Encoded, numberOfNeighbors);
	EXPECT_FALSE(*rule110 == *rule110With5Neighbors)
		<< "The same rule encodings with different number of Neighbors compare as equal.";
}

TEST_F(KNearestNeighborsRuleTest, ShouldThrowOnInvalidNumberOfNeighbors)
{
	auto invalidNumberOfNeighbors = KNearestNeighborsRule::MIN_NUMBER_OF_NEIGHBORS - 1;
	state_t numberOfStates = 2;
	integer_t integer = 56;
	BaseBInteger integerEncodedRule(numberOfStates, integer);
	EXPECT_THROW(KNearestNeighborsRule::createPtr(integerEncodedRule, invalidNumberOfNeighbors), std::domain_error);
}

}
