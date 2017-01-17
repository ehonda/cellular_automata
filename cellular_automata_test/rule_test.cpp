#include "gtest/gtest.h"

#include "rule.h"
#include "rule.cpp"
#include "rule_stub.h"
#include "rule_stub.cpp"

using namespace cellular_automata;
using namespace integers;

TEST(RuleTest, GettingNumberOfStatesWorks)
{
	state_t expectedNumberOfStates = 55;
	auto ruleStub = RuleStub::createPtr(expectedNumberOfStates);
	state_t actualNumberOfStates = ruleStub->getNumberOfStates();
	EXPECT_EQ(expectedNumberOfStates, actualNumberOfStates);
}

TEST(RuleTest, ComparisonForEqualityWorks)
{
	state_t numberOfStates = 44444;
	auto rule1 = RuleStub::createPtr(numberOfStates);
	auto rule2 = RuleStub::createPtr(numberOfStates);
	EXPECT_TRUE(*rule1 == *rule2) << "The same rules compare as different";

	state_t otherNumberOfStates = 50;
	auto rule3 = RuleStub::createPtr(otherNumberOfStates);
	EXPECT_FALSE(*rule1 == *rule3) << "Different rules compare as equal";
}