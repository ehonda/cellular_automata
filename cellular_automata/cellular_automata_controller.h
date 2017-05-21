#pragma once

#include "cellular_automaton.h"
#include "type_definitions.h"

namespace cellular_automata_mvc {

class CellularAutomataController {
public:
	CellularAutomataController() = default;
	CellularAutomataController(const cellular_automata::CellVector& initialCells,
		const cellular_automata::RulePtr& rule);

	void iterate();
	void transitionToRandomRule();

	const cellular_automata::CellRow& getCurrentGeneration() const noexcept;
	cellular_automata::CellularAutomatonPtr getCellularAutomaton() const noexcept;

private:
	cellular_automata::CellularAutomatonPtr automaton_;
};

}
