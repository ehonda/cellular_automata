#include "gtest/gtest.h"
#include "basic_rules.h"

#include "cell_row.h"
#include "bounded_cell_row_boundary_component.h"

namespace cellular_automata_test {

using namespace cellular_automata;

class BoundedCellRowBoundaryComponentTest
	: public testing::Test {
protected:
	BoundedCellRowBoundaryComponentTest() {
		CellVector cells = { 1, 1, 1 };
		auto rule = BasicRules::getKnnRule(2, 30, 3);
		CellRow row(cells, rule);
		component_ = BoundedCellRowBoundaryComponent(&row);
	}

	//################################################################
	// Domain specific language

	void expectCellAtDistanceFromFirst(const Cell& cell, size_t distance) {
		Cell outsideCell = component_.getCellBeforeFirstCellInRow(distance);
		EXPECT_EQ(cell, outsideCell);
	}

	void expectCellAtDistanceFromLast(const Cell& cell, size_t distance) {
		Cell outsideCell = component_.getCellBeyondLastCellInRow(distance);
		EXPECT_EQ(cell, outsideCell);
	}

	// End Domain specific language
	//################################################################


	BoundedCellRowBoundaryComponent component_;
};

TEST_F(BoundedCellRowBoundaryComponentTest,
	test_cells_before_first_cell) {
	expectCellAtDistanceFromFirst(Cell(0), 1);
	expectCellAtDistanceFromFirst(Cell(0), 2);
}

TEST_F(BoundedCellRowBoundaryComponentTest,
	test_cells_beyond_last_cell) {
	expectCellAtDistanceFromLast(Cell(0), 1);
	expectCellAtDistanceFromLast(Cell(0), 2);
}

TEST_F(BoundedCellRowBoundaryComponentTest,
	test_different_boundary_value) {
	Cell boundaryCell(1);
	component_.setBoundaryCell(boundaryCell);

	expectCellAtDistanceFromFirst(boundaryCell, 1);
	expectCellAtDistanceFromLast(boundaryCell, 1);
}

TEST_F(BoundedCellRowBoundaryComponentTest,
	test_comparison_for_equality) {
	auto copiedComponent(component_);
	EXPECT_EQ(copiedComponent, component_);

	BoundedCellRowBoundaryComponent componentWithDifferentBoundaryCell;
	componentWithDifferentBoundaryCell.setBoundaryCell(1);
	EXPECT_NE(componentWithDifferentBoundaryCell, component_);
}

}
