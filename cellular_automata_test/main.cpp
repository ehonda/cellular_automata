#include <iostream>
#include <conio.h>

#include "gtest/gtest.h"

int main(int argc, char **argv) {
	std::cout << "Running main() from cellular_automata_test/main.cpp\n";
	testing::InitGoogleTest(&argc, argv);
	int testResults = RUN_ALL_TESTS();

	std::cout << "Press any key to end";
	_getch();
	return testResults;
}
