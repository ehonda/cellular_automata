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
		component = BoundedCellRowBoundaryComponent(&row);
	}

	void expectCellAtDistanceFromFirst(const Cell& cell, size_t distance) {
		Cell outsideCell = component.getCellBeforeFirstCellInRow(distance);
		EXPECT_EQ(cell, outsideCell);
	}

	void expectCellAtDistanceFromLast(const Cell& cell, size_t distance) {
		Cell outsideCell = component.getCellBeyondLastCellInRow(distance);
		EXPECT_EQ(cell, outsideCell);
	}

	BoundedCellRowBoundaryComponent component;
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
	component.setBoundaryCell(boundaryCell);

	expectCellAtDistanceFromFirst(boundaryCell, 1);
	expectCellAtDistanceFromLast(boundaryCell, 1);
}

}
