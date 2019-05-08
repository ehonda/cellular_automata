#include "cellular_automaton_app.h"
#include "k_nearest_neighbors_rule.h"

int main(int argc, char* args[])
{
	using namespace cellular_automata;
	auto app = CellularAutomatonApp::getInstance();

	int states = 3;
	int neighbors = 3;
	mpz_class encoding("3569747533542", 10);
	if (argc == 4) {
		try {
			states = std::stoi(args[1]);
			neighbors = std::stoi(args[2]);
			encoding = mpz_class(args[3], 10);
		}
		catch (std::exception e) {
			int states = 3;
			int neighbors = 3;
			mpz_class encoding("3569747533542", 10);
		}
	}

	auto rule = KNearestNeighborsRule::createPtr(
		integers::BaseBInteger(states, encoding),
		neighbors
	);

	app->setRandomInitialGeneration(states);
	//app->setRule(rule);
	//app->setRandomKNNRule(states, neighbors);
	//app->setRule(rule->getRandomRuleOfSameType());
	app->setRule(rule);

	return app->execute(argc, args);
}
