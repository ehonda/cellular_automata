#include "gtest/gtest.h"
#include "basic_rules.h"

#include "cellular_automata_controller.h"

namespace cellular_automata_test {

using namespace cellular_automata;
using namespace cellular_automata_mvc;

class CellularAutomataControllerTest : public testing::Test {
protected:
	CellularAutomataControllerTest() {
		defaultRule_ = BasicRules::getSierpinskiRule();
		controller_ = CellularAutomataController({ 0, 0, 1, 0, 0 }, defaultRule_);
	}

	//################################################################
	// Domain specific language

	void setDefaultRule(const RulePtr& rule) {
		defaultRule_ = rule;
	}

	void setInitialCells(const CellVector& cells) {
		controller_ = CellularAutomataController(cells, defaultRule_);
	}

	void expectAfterIteration(const CellVector& cells) {
		controller_.iterate();
		auto gen = controller_.getCurrentGeneration();
		auto expectedGen = CellRow(cells, defaultRule_);
	}

	// End Domain specific language
	//################################################################

	RulePtr defaultRule_;
	CellularAutomataController controller_;
};

TEST_F(CellularAutomataControllerTest, test_iterate_one) {
	setDefaultRule(BasicRules::getSierpinskiRule());
	setInitialCells		({ 0, 0, 1, 0, 0 });
	expectAfterIteration({ 0, 1, 0, 1, 0 });
}

}
