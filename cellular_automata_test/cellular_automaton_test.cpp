#include <stdexcept>

#include "gtest/gtest.h"
#include "basic_rules.h"

#include "cellular_automaton.h"

#include "base_b_integer.h"
#include "bounded_cell_row.h"
#include "k_nearest_neighbors_rule.h"
#include "k_nearest_neighbors_cell_neighborhood_creator.h"
#include "type_definitions.h"

namespace cellular_automata_test {

using namespace cellular_automata;
using namespace integers;

//-----------------------------------------------------------------------------------------------
//TEST FIXTURE CLASS

class CellularAutomatonTest : public testing::Test
{
protected:
	virtual void SetUp()
	{
		BaseBInteger rule90Encoded(2, 90);
		integer_t numberOfNeighbors = 3;
		_rule90 = KNearestNeighborsRule::createPtr(rule90Encoded, numberOfNeighbors);

		_initialGeneration = { 0, 0, 1, 0, 0 };
		automaton_ = CellularAutomaton(getInitialGeneration());
		defaultRule_ = BasicRules::getSierpinskiRule();
	}

	virtual CellNeighborhoodCreatorPtr getKnnNeighborhoodCreator() const noexcept
	{
		return std::make_unique<KNearestNeighborsCellNeighborhoodCreator>(_rule90);
	}

	CellRowPtr getInitialGeneration()
	{
		return std::make_shared<BoundedCellRow>(getKnnNeighborhoodCreator(), _initialGeneration);
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
		CellRow nextGeneration = automaton_.advanceToNextGeneration2();
		EXPECT_EQ(nextGeneration, expectedNextGeneration);
	}

	//Old
	//----------------------------------------------------------------

	void initialCells(const CellVector& cells) {
		CellRowPtr initialGen = std::make_shared<BoundedCellRow>(
			getKnnNeighborhoodCreator(), cells);
		automaton_ = CellularAutomaton(initialGen);
	}

	void expectNextGen(const CellVector& cells) {
		CellRowPtr expectedNextGeneration = std::make_shared<BoundedCellRow>(getKnnNeighborhoodCreator(), cells);
		CellRowPtr actualNextGeneration = automaton_.getNextGeneration();
		EXPECT_EQ(*actualNextGeneration, *expectedNextGeneration);
	}

	// End Domain specific language
	//################################################################

	//old
	KNearestNeighborsRulePtr _rule90;
	//old
	CellVector _initialGeneration;

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

TEST_F(CellularAutomatonTest, Get_one_step) {
	initialCells({ 0, 0, 1, 0, 0 });
	expectNextGen({ 0, 1, 0, 1, 0 });
}

TEST_F(CellularAutomatonTest, Get_three_steps) {
	initialCells ({ 0, 0, 0, 1, 0, 0, 0 });
	expectNextGen({ 0, 0, 1, 0, 1, 0, 0 });
	expectNextGen({ 0, 1, 0, 0, 0, 1, 0 });
	expectNextGen({ 1, 0, 1, 0, 1, 0, 1 });
}

TEST_F(CellularAutomatonTest, Should_throw_on_creation_from_nullptr) {
	EXPECT_THROW(CellularAutomaton(CellRowPtr(nullptr)), std::invalid_argument);
}

//-----------------------------------------------------------------------------------------------


}
