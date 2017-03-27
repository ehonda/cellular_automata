#include <stdexcept>

#include "gtest/gtest.h"

#include "cell_neighborhood_creator.h"
#include "cell_neighborhood_creator_stub.h"

#include "k_nearest_neighbors_rule.h"

namespace
{

using namespace cellular_automata;
using namespace integers;

//-----------------------------------------------------------------------------------------------
//TEST FIXTURE CLASS

class CellNeighborhoodCreatorTest : public testing::Test
{
protected:
	virtual void SetUp()
	{
		BaseBInteger someBase10RuleEncoded(10, 111);
		integer_t numberOfNeighbors = 3;
		_knnRule = KNearestNeighborsRule::createPtr(someBase10RuleEncoded, numberOfNeighbors);

		integer_t differentNumberOfNeighbors = 5;
		_differentKnnRule = KNearestNeighborsRule::createPtr(someBase10RuleEncoded, differentNumberOfNeighbors);
	}

	KNearestNeighborsRulePtr _knnRule;
	KNearestNeighborsRulePtr _differentKnnRule;
};

//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
//TEST CASES

TEST_F(CellNeighborhoodCreatorTest, ConstructionWorks)
{
	CellNeighborhoodCreatorStub creator(_knnRule);
	auto rule = creator.getRule();
	EXPECT_EQ(*_knnRule, *rule);
}

TEST_F(CellNeighborhoodCreatorTest, ShouldThrowWhenInitializedWithNullPtr)
{
	RulePtr null(nullptr);
	EXPECT_THROW(CellNeighborhoodCreatorStub creator(null), std::invalid_argument);
}

TEST_F(CellNeighborhoodCreatorTest, ComparisonForEqualityWorks)
{
	CellNeighborhoodCreatorStub creator(_knnRule);
	CellNeighborhoodCreatorStub creatorWithSameRule(_knnRule);
	EXPECT_EQ(creator, creatorWithSameRule);

	CellNeighborhoodCreatorStub creatorWithDifferentRule(_differentKnnRule);
	EXPECT_NE(creator, creatorWithDifferentRule);
}

//-----------------------------------------------------------------------------------------------

}
