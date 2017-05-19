#include <stdexcept>

#include "gtest/gtest.h"
#include "basic_rules.h"

#include "cell_row.h"

#include "bounded_cell_row_boundary_component.h"
#include "type_definitions.h"

namespace cellular_automata_test {

using namespace cellular_automata;
using namespace integers;

//-----------------------------------------------------------------------------------------------
//TEST FIXTURE CLASS

class CellRowTest : public testing::Test {
protected:
	CellRowTest() {
		setDefaultRule(BasicRules::getElementaryRule(30));
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

	void setBoundaryCell(const Cell& boundaryCell, CellRow& row) {
		std::unique_ptr<BoundedCellRowBoundaryComponent> boundaryComponent(
			new BoundedCellRowBoundaryComponent());
		boundaryComponent->setBoundaryCell(boundaryCell);
		row.setBoundaryComponent(std::move(boundaryComponent));
	}

	void setBoundaryCell(const Cell& boundaryCell) {
		setBoundaryCell(boundaryCell, row_);
	}

	void expectCellNeighborhoodAroundCenter(
		const CellVector& expectedCells, const CellRow& row,
		const CellVector::const_iterator& center) const {
		auto actualCells = row.getCellNeighborhood(center);
		EXPECT_EQ(actualCells, expectedCells);
	}

	void expectCellNeighborhoodAroundCenter(
		const CellVector& expectedCells) const {
		expectCellNeighborhoodAroundCenter(expectedCells, row_, center_);
	}

	// End Domain specific language
	//################################################################

	CellRow row_;
	CellVector::const_iterator center_;
	RulePtr defaultRule_;
};

//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
//TEST CASES

TEST_F(CellRowTest, test_inner_cell_neighborhood) {
	makeCellRow({ 0, 0, 1, 1, 1, 0, 0 });
	centerAtPosition(1);
	expectCellNeighborhoodAroundCenter({ 0, 0, 1 });
}

TEST_F(CellRowTest, test_outer_neighborhood) {
	setDefaultRule(BasicRules::getKnnRule(3, 100, 7));
	makeCellRow({ 0, 0, 1 });
	setBoundaryCell(2);
	centerAtPosition(1);
	expectCellNeighborhoodAroundCenter({ 2, 2, 0, 0, 1, 2, 2 });
}

TEST_F(CellRowTest, test_copy_assignment) {
	makeCellRow({ 0, 0, 1 });

	auto copy = row_;
	setBoundaryCell(1, copy);

	EXPECT_NE(row_, copy);
}

TEST_F(CellRowTest, test_empty_cell_row_copy) {
	CellRow emptyRow;
	CellRow copy = emptyRow;
	EXPECT_EQ(emptyRow, copy);
}

TEST_F(CellRowTest, test_comparison_operator)
{
	makeCellRow({ 0, 0, 0 });
	CellRow sameRow(row_);
	EXPECT_EQ(row_, sameRow);

	CellRow rowWithDifferentCells;
	makeCellRow({ 1, 1, 1 }, rowWithDifferentCells);
	EXPECT_NE(row_, rowWithDifferentCells);

	CellRow rowWithDifferentBoundary(row_);
	setBoundaryCell(1, rowWithDifferentBoundary);
	EXPECT_NE(row_, rowWithDifferentBoundary);

	setDefaultRule(BasicRules::getElementaryRule(255));
	CellRow rowWithDifferentRule;
	makeCellRow({ 0, 0, 0 }, rowWithDifferentRule);
	EXPECT_NE(row_, rowWithDifferentRule);
}

TEST_F(CellRowTest, get_neighborhood_and_get_rule_throw_on_uninitialised_row) {
	CellRow row;
	EXPECT_THROW(row.getCellNeighborhood(center_), std::logic_error);
	EXPECT_THROW(row.getRule(), std::logic_error);
}

//-----------------------------------------------------------------------------------------------

}
