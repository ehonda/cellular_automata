#include "cellular_automaton_app.h"

int main(int argc, char* args[])
{
	auto app = cellular_automaton::CellularAutomatonApp::getInstance();
	return app->execute(argc, args);
}
