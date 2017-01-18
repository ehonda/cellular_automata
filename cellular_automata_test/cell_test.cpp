#include "gtest/gtest.h"

#include "cell.h"
#include "cell.cpp"

TEST(CellTest, ConstructionAndSettingStateWork)
{
	using namespace cellular_automata;
	using namespace integers;
	
	state_t expectedState = 0;
	Cell emptyCell;
	state_t actualState = emptyCell.getState();
	EXPECT_EQ(expectedState, actualState) << "Empty cell does not construct properly.";

	expectedState = 42;
	Cell filledCell(expectedState);
	actualState = filledCell.getState();
	EXPECT_EQ(expectedState, actualState) << "Filled cell does not construct properly.";

	expectedState = 99;
	filledCell.setState(expectedState);
	actualState = filledCell.getState();
	EXPECT_EQ(expectedState, actualState) << "Setting filled cell state does not work.";
}
