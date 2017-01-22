#include <memory>

#include "gtest/gtest.h"

#include "cell_population.h"
#include "cell_population.cpp"

namespace
{

using namespace cellular_automata;

//-----------------------------------------------------------------------------------------------
//TEST FIXTURE CLASS

class CellPopulationTest : public testing::Test
{
protected:
	std::unique_ptr<CellPopulation> makeInstance() const;
};

}