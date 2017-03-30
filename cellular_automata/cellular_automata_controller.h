#pragma once

#include "cellular_automaton.h"
#include "type_definitions.h"

namespace cellular_automata_mvc {

class CellularAutomataController {
public:
	CellularAutomataController() = default;
	CellularAutomataController(
		const cellular_automata::KNearestNeighborsRulePtr& rule,
		const cellular_automata::CellVector& initialCells);

	void iterate();

	cellular_automata::CellRowPtr getCurrentGeneration() const;
	cellular_automata::CellularAutomatonPtr getCellularAutomaton() const;

private:
	cellular_automata::CellularAutomatonPtr automaton_;
};

}
