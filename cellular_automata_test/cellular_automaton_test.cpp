#include "gtest/gtest.h"

#include "cellular_automaton.h"
#include "cellular_automaton.cpp"

#include "base_b_integer.h"
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

	KNearestNeighborsRulePtr _rule30;
	CellVector _initialGeneration;
};

//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
//TEST CASES

//TEST_F(CellularAutomatonTest, )

//-----------------------------------------------------------------------------------------------


}
