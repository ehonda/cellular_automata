#include <memory>

#include "gtest/gtest.h"
#include "basic_rules.h"

#include "k_nearest_neighbors_cell_neighborhood_creator.h"

#include "cell_neighborhood_creator_factory.h"
#include "cell_row.h"
#include "type_definitions.h"

namespace cellular_automata_test {

using namespace cellular_automata;
using namespace integers;

//-----------------------------------------------------------------------------------------------
//TEST FIXTURE CLASS

class KNearestNeighborsCellNeighborhoodCreatorTest
	: public testing::Test {
protected:

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
		CellNeighborhoodCreatorPtr& creator) {
		makeCellRow(cells);
		creator = CellNeighborhoodCreatorFactory::getCreator(defaultRule_, &row_);
	}

	void makeCreatorFor(const CellVector& cells) {
		makeCreatorFor(cells, creator_);
	}

	void expectCellNeighborhoodAroundCenter(
		const CellVector& expectedCells, 
		const CellNeighborhoodCreatorPtr& creator,
		const CellVector::const_iterator& center) const {
		auto actualCells = creator->createCellNeighborhood(center);
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
	CellNeighborhoodCreatorPtr creator_;
};

typedef KNearestNeighborsCellNeighborhoodCreatorTest KNearestNeighborsCellNeighborhoodCreatorDeathTest;

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

TEST_F(KNearestNeighborsCellNeighborhoodCreatorTest,
	test_neighborhood_around_begin) {
	setDefaultRule(BasicRules::getKnnRule(4, 100, 3));
	makeCreatorFor({ 1, 2, 3 });
	centerAtPosition(0);
	expectCellNeighborhoodAroundCenter({ 0, 1, 2 });
}

TEST_F(KNearestNeighborsCellNeighborhoodCreatorTest,
	test_neighborhood_before_end) {
	setDefaultRule(BasicRules::getKnnRule(4, 100, 3));
	makeCreatorFor({ 1, 2, 3 });
	centerAtPosition(2);
	expectCellNeighborhoodAroundCenter({ 2, 3, 0 });
}

TEST_F(KNearestNeighborsCellNeighborhoodCreatorTest,
	test_throw_on_center_around_cend) {
	setDefaultRule(BasicRules::getKnnRule(4, 100, 3));
	makeCreatorFor({ 1, 2, 3 });
	centerAtPosition(3);
	EXPECT_THROW(expectCellNeighborhoodAroundCenter({ 3, 0, 0 }), std::invalid_argument);
}

TEST_F(KNearestNeighborsCellNeighborhoodCreatorTest,
	test_make_copy_for_row) {
	setDefaultRule(BasicRules::getKnnRule(4, 100, 3));
	makeCreatorFor({ 1, 1, 1 });
	
	CellRow rowForCopy({ 2, 2, 2 }, defaultRule_);
	auto copy = creator_->makeCopyFor(&rowForCopy);

	centerAtPosition(1);
	expectCellNeighborhoodAroundCenter({ 1, 1, 1 });

	CellVector::const_iterator center;
	centerAtPosition(1, rowForCopy, center);
	expectCellNeighborhoodAroundCenter({ 2, 2, 2 }, copy, center);
}

//-----------------------------------------------------------------------------------------------

}
