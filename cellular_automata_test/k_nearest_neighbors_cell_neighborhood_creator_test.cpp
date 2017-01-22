#include "gtest/gtest.h"

#include "k_nearest_neighbors_cell_neighborhood_creator.h"
#include "k_nearest_neighbors_cell_neighborhood_creator.cpp"

#include "cell_neighborhood_creator.h"
#include "k_nearest_neighbors_rule.h"
#include "type_definitions.h"

namespace
{

using namespace cellular_automata;
using namespace integers;

//-----------------------------------------------------------------------------------------------
//TEST FIXTURE CLASS

class KNearestNeighborsCellNeighborhoodCreatorTest : public testing::Test
{
protected:
	virtual void SetUp()
	{
		BaseBInteger someBase10RuleEncoded(10, 111);

		_evenNumberOfNeighbors = 4;
		_knnRuleWithEvenNumberOfNeighbors
			= KNearestNeighborsRule::createPtr(someBase10RuleEncoded, _evenNumberOfNeighbors);

		_oddNumberOfNeighbors = 5;
		_knnRuleWithOddNumberOfNeighbors
			= KNearestNeighborsRule::createPtr(someBase10RuleEncoded, _oddNumberOfNeighbors);

		_integersFrom0To9 = CellVector{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	}

	CellVector _integersFrom0To9;
	integer_t _evenNumberOfNeighbors;
	integer_t _oddNumberOfNeighbors;
	KNearestNeighborsRulePtr _knnRuleWithEvenNumberOfNeighbors;
	KNearestNeighborsRulePtr _knnRuleWithOddNumberOfNeighbors;
};

//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
//TEST CASES

TEST_F(KNearestNeighborsCellNeighborhoodCreatorTest, EvenNumberOfNeighborsWorks)
{
	KNearestNeighborsCellNeighborhoodCreator creator(_knnRuleWithEvenNumberOfNeighbors);

	CellVector expectedCellsInNeighborhood{ 2, 3, 4, 5 };
	auto expectedCellNeighborhood
		= CellNeighborhood::createPtr(expectedCellsInNeighborhood, _knnRuleWithEvenNumberOfNeighbors);

	auto center = _integersFrom0To9.begin() + 4;
	auto actualCellNeighborhood = creator.createCellNeighborhood(center);

	EXPECT_EQ(*expectedCellNeighborhood, *actualCellNeighborhood);
}

TEST_F(KNearestNeighborsCellNeighborhoodCreatorTest, OddNumberOfNeighborsWorks)
{
	KNearestNeighborsCellNeighborhoodCreator creator(_knnRuleWithOddNumberOfNeighbors);

	CellVector expectedCellsInNeighborhood{ 2, 3, 4, 5, 6 };
	auto expectedCellNeighborhood
		= CellNeighborhood::createPtr(expectedCellsInNeighborhood, _knnRuleWithOddNumberOfNeighbors);

	auto center = _integersFrom0To9.begin() + 4;
	auto actualCellNeighborhood = creator.createCellNeighborhood(center);

	EXPECT_EQ(*expectedCellNeighborhood, *actualCellNeighborhood);
}

TEST_F(KNearestNeighborsCellNeighborhoodCreatorTest, ComparisonForEqualityWorks)
{
	KNearestNeighborsCellNeighborhoodCreator creator(_knnRuleWithEvenNumberOfNeighbors);
	KNearestNeighborsCellNeighborhoodCreator sameCreator(_knnRuleWithEvenNumberOfNeighbors);
	EXPECT_EQ(creator, sameCreator);

	KNearestNeighborsCellNeighborhoodCreator creatorWithDifferentRule(_knnRuleWithOddNumberOfNeighbors);
	EXPECT_NE(creator, creatorWithDifferentRule);
}

TEST_F(KNearestNeighborsCellNeighborhoodCreatorTest, GettingPointerToCopyWorks)
{
	CellNeighborhoodCreatorPtr creator(new KNearestNeighborsCellNeighborhoodCreator(_knnRuleWithEvenNumberOfNeighbors));
	auto creatorCopy = creator->getPtrToCopy();
	EXPECT_EQ(*creator, *creatorCopy);
}

//-----------------------------------------------------------------------------------------------

}
