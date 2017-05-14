#include "gtest/gtest.h"
#include "basic_rules.h"

#include "k_nearest_neighbors_cell_neighborhood_creator.h"

#include "cell_neighborhood_creator.h"
#include "cell_row.h"
#include "k_nearest_neighbors_rule.h"
#include "type_definitions.h"

namespace cellular_automata_test {

using namespace cellular_automata;
using namespace integers;

//-----------------------------------------------------------------------------------------------
//TEST FIXTURE CLASS

class KNearestNeighborsCellNeighborhoodCreatorTest
	: public testing::Test {
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
	
		defaultRule_ = BasicRules::getKnnRule(12, 100, 3);
		//makeCellRow(_integersFrom0To9);
		//creator_ = KNearestNeighborsCellNeighborhoodCreator(defaultRule_, &row_);
	}

	//################################################################
	// Domain specific language

	virtual void setDefaultRule(const RulePtr& rule) {
		defaultRule_ = rule;
	}

	void makeCellRow(const CellVector& cells, CellRow& row) {
		row = CellRow(cells, defaultRule_);
	}

	void makeCellRow(const CellVector& cells) {
		makeCellRow(cells, row_);
	}

	void centerAtPosition(size_t index, const CellRow& row,
		CellVector::const_iterator& center) {
		center = row.cbegin() + index;
	}

	void centerAtPosition(size_t index) {
		centerAtPosition(index, row_, center_);
	}

	void makeCreatorFor(const CellVector& cells,
		KNearestNeighborsCellNeighborhoodCreator& creator) {
		makeCellRow(cells);
		creator = KNearestNeighborsCellNeighborhoodCreator(
			defaultRule_, &row_);
	}

	void makeCreatorFor(const CellVector& cells) {
		makeCreatorFor(cells, creator_);
	}

	void expectCellNeighborhoodAroundCenter(
		const CellVector& expectedCells, 
		const KNearestNeighborsCellNeighborhoodCreator& creator,
		const CellVector::const_iterator& center) const {
		auto actualCells = creator.createCellNeighborhood2(center);
		EXPECT_EQ(actualCells, expectedCells);
	}

	void expectCellNeighborhoodAroundCenter(
		const CellVector& expectedCells) const {
		expectCellNeighborhoodAroundCenter(expectedCells, creator_, center_);
	}

	// End Domain specific language
	//################################################################

	RulePtr defaultRule_;
	CellRow row_;
	CellVector::const_iterator center_;
	KNearestNeighborsCellNeighborhoodCreator creator_;

	CellVector _integersFrom0To9;
	integer_t _evenNumberOfNeighbors;
	integer_t _oddNumberOfNeighbors;
	KNearestNeighborsRulePtr _knnRuleWithEvenNumberOfNeighbors;
	KNearestNeighborsRulePtr _knnRuleWithOddNumberOfNeighbors;
};

//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
//TEST CASES

TEST_F(KNearestNeighborsCellNeighborhoodCreatorTest,
	test_neighborhood2_inner_even) {
	setDefaultRule(BasicRules::getKnnRule(4, 100, 5));
	makeCreatorFor({ 1, 2, 3, 2, 1 });
	centerAtPosition(2);
	expectCellNeighborhoodAroundCenter({ 1, 2, 3, 2, 1 });
}

TEST_F(KNearestNeighborsCellNeighborhoodCreatorTest,
	test_neighborhood2_inner_odd) {
	setDefaultRule(BasicRules::getKnnRule(4, 100, 4));
	makeCreatorFor({ 1, 2, 3, 2, 1 });
	centerAtPosition(2);
	expectCellNeighborhoodAroundCenter({ 1, 2, 3, 2 });
}

TEST_F(KNearestNeighborsCellNeighborhoodCreatorTest,
	test_neighborhood2_outer) {
	setDefaultRule(BasicRules::getKnnRule(4, 100, 9));
	makeCreatorFor({ 1, 2, 3, 2, 1 });
	centerAtPosition(2);
	expectCellNeighborhoodAroundCenter(
	{0, 0, 1, 2, 3, 2, 1, 0, 0 });
}

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
