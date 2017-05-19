#include "gtest/gtest.h"
#include "basic_rules.h"

#include "cellular_automaton.h"
#include "type_definitions.h"

namespace cellular_automata_test {

using namespace cellular_automata;
using namespace integers;

//-----------------------------------------------------------------------------------------------
//TEST FIXTURE CLASS

class CellularAutomatonTest : public testing::Test {
protected:
	CellularAutomatonTest() 
		: defaultRule_(BasicRules::getSierpinskiRule()) {
	}

	//################################################################
	// Domain specific language

	void setDefaultRule(const RulePtr& rule) {
		defaultRule_ = rule;
	}

	void setInitialCells(const CellVector& cells) {
		automaton_ = CellularAutomaton(cells, defaultRule_);
	}

	void expectNextGeneration(const CellVector& cells) {
		CellRow expectedNextGeneration(cells, defaultRule_);
		CellRow nextGeneration = automaton_.advanceToNextGeneration();
		EXPECT_EQ(nextGeneration, expectedNextGeneration);
	}

	// End Domain specific language
	//################################################################

	RulePtr defaultRule_;
	CellularAutomaton automaton_;
};

//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
//TEST CASES

TEST_F(CellularAutomatonTest, get_one_step) {
	setInitialCells		({ 0, 0, 1, 0, 0 });
	expectNextGeneration({ 0, 1, 0, 1, 0 });
}

TEST_F(CellularAutomatonTest, get_three_steps) {
	setInitialCells		({ 0, 0, 0, 1, 0, 0, 0 });
	expectNextGeneration({ 0, 0, 1, 0, 1, 0, 0 });
	expectNextGeneration({ 0, 1, 0, 0, 0, 1, 0 });
	expectNextGeneration({ 1, 0, 1, 0, 1, 0, 1 });
}

//-----------------------------------------------------------------------------------------------

}
