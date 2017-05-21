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

	void makeController(const CellVector& initialCells) {
		controller_ = CellularAutomataController(initialCells, defaultRule_);
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
	makeController		({ 0, 0, 1, 0, 0 });
	expectAfterIteration({ 0, 1, 0, 1, 0 });
}

TEST_F(CellularAutomataControllerTest, random_reset_3_states_3_neighbors) {
	setDefaultRule(BasicRules::getKnnRule(3, 0, 3));
	makeController({0, 1, 0});
	RulePtr beforeReset = defaultRule_;
	auto lastGenBeforeReset = controller_.getCurrentGeneration();

	controller_.transitionToRandomRule();
	RulePtr afterReset = controller_.getCellularAutomaton()->getRule();
	auto firstGenAfterReset = controller_.getCurrentGeneration();

	ASSERT_EQ(lastGenBeforeReset.getCells(), firstGenAfterReset.getCells());
	EXPECT_NE(*beforeReset, *afterReset) << "Probabilistic Test with very small probability failed";
}

}
