#include "gtest/gtest.h"

#include "cellular_automata_controller.h"
#include "k_nearest_neighbors_rule.h"
#include "bounded_cell_row.h"

namespace {
using namespace cellular_automata;

class CellularAutomataControllerTest : public testing::Test {
protected:
	KNearestNeighborsRulePtr getRule30() {
		integers::BaseBInteger encodedRule(2, 30);
		size_t neighbors = 3;
		//return std::make_shared<KNearestNeighborsRule>(encodedRule, neighbors);
		return KNearestNeighborsRulePtr();
	}

	BoundedCellRowPtr getInitialCellRow() {
		return BoundedCellRowPtr();
	}
};

TEST_F(CellularAutomataControllerTest, test_iterate_once) {
	//CellularAutomataController c(getRule30(), );
	/*c.setRule(getRule30());
	c.setCellRow()*/
}
}