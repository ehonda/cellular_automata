#include "cellular_automaton_app.h"
#include "k_nearest_neighbors_rule.h"

int main(int argc, char* args[])
{
	using namespace cellular_automata;
	auto app = CellularAutomatonApp::getInstance();

	int states = 3;
	int neighbors = 3;
	auto rule = KNearestNeighborsRule::createPtr(
		integers::BaseBInteger(states, 14),
		neighbors
	);

	app->setRandomInitialGeneration(states);
	//app->setRule(rule);
	app->setRandomKNNRule(states, neighbors);

	return app->execute(argc, args);
}
