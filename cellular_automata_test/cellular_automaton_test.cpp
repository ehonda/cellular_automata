#include <stdexcept>

#include "gtest/gtest.h"

#include "cellular_automaton.h"

#include "base_b_integer.h"
#include "bounded_cell_row.h"
#include "k_nearest_neighbors_rule.h"
#include "k_nearest_neighbors_cell_neighborhood_creator.h"
#include "type_definitions.h"

namespace
{

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
		automaton = CellularAutomaton(getInitialGeneration());
	}

	virtual CellNeighborhoodCreatorPtr getKnnNeighborhoodCreator() const noexcept
	{
		return std::make_unique<KNearestNeighborsCellNeighborhoodCreator>(_rule90);
	}

	CellRowPtr getInitialGeneration()
	{
		return std::make_shared<BoundedCellRow>(getKnnNeighborhoodCreator(), _initialGeneration);
	}

	void initialCells(const CellVector& cells) {
		CellRowPtr initialGen = std::make_shared<BoundedCellRow>(getKnnNeighborhoodCreator(), cells);
		automaton = CellularAutomaton(initialGen);
	}

	void expectNextGen(const CellVector& cells) {
		CellRowPtr expectedNextGeneration = std::make_shared<BoundedCellRow>(getKnnNeighborhoodCreator(), cells);
		CellRowPtr actualNextGeneration = automaton.getNextGeneration();
		EXPECT_EQ(*actualNextGeneration, *expectedNextGeneration);
	}

	KNearestNeighborsRulePtr _rule90;
	CellVector _initialGeneration;
	CellularAutomaton automaton;
};

//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
//TEST CASES

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
