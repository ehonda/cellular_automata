#include <stdexcept>

#include "gtest/gtest.h"

#include "cellular_automaton.h"
//#include "cellular_automaton.cpp"

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
		BaseBInteger rule30Encoded(2, 30);
		integer_t numberOfNeighbors = 3;
		_rule30 = KNearestNeighborsRule::createPtr(rule30Encoded, numberOfNeighbors);

		_initialGeneration = { 0, 0, 1, 0, 0 };
	}

	virtual CellNeighborhoodCreatorPtr getKnnNeighborhoodCreator() const noexcept
	{
		return std::make_unique<KNearestNeighborsCellNeighborhoodCreator>(_rule30);
	}

	CellRowPtr getInitialGeneration()
	{
		return std::make_shared<BoundedCellRow>(getKnnNeighborhoodCreator(), _initialGeneration);
	}

	KNearestNeighborsRulePtr _rule30;
	CellVector _initialGeneration;
};

//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
//TEST CASES

//TEST_F(CellularAutomatonTest, Get_one_step)
//{
//	CellularAutomaton automaton(getInitialGeneration());
//
//	CellVector exptectedCellsNextStep = { 0, 1, 0, 1, 0 };
//	CellRowPtr expectedNextGeneration = std::make_shared<BoundedCellRow>(getKnnNeighborhoodCreator(), exptectedCellsNextStep);
//	CellRowPtr actualNextGeneration = automaton.getNextGeneration();
//	EXPECT_EQ(*actualNextGeneration, *expectedNextGeneration);
//}

//TEST_F(CellularAutomatonTest, Should_throw_on_creation_from_nullptr)
//{
//	EXPECT_THROW(CellularAutomaton(CellRowPtr(nullptr)), std::invalid_argument);
//}

//-----------------------------------------------------------------------------------------------


}
