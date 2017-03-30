#include "gtest/gtest.h"
#include "basic_rules.h"

#include "cellular_automata_controller.h"
#include "k_nearest_neighbors_rule.h"
#include "bounded_cell_row.h"

namespace cellular_automata_test {

using namespace cellular_automata;
using namespace cellular_automata_mvc;

class CellularAutomataControllerTest : public testing::Test {
protected:
	CellularAutomataControllerTest() {
		c = CellularAutomataController(rule90, initCells);
	}

	void expectGen(const CellVector& cells) {
		auto gen = c.getCurrentGeneration();
		auto expectedGen = CellRowPtr(new BoundedCellRow(rule90, cells));
		EXPECT_EQ(*gen, *expectedGen);
	}

	KNearestNeighborsRulePtr rule90 = BasicRules::getElementaryRule(90);
	CellVector initCells = { 0, 0, 1, 0, 0 };
	CellularAutomataController c;
};

TEST_F(CellularAutomataControllerTest, test_gen_0) {
	expectGen(initCells);
}

TEST_F(CellularAutomataControllerTest, test_iterate_one) {
	c.iterate();
	expectGen({ 0, 1, 0, 1, 0 });
}

}
