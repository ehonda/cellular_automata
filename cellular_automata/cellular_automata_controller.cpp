#include "cellular_automata_controller.h"

namespace cellular_automata_mvc {

CellularAutomataController::CellularAutomataController(
	const cellular_automata::CellVector& initialCells,
	const cellular_automata::RulePtr& rule) {
	automaton_ = std::make_shared<cellular_automata::CellularAutomaton>(initialCells, rule);
}

void CellularAutomataController::iterate()
{
	automaton_->advanceToNextGeneration();
}

const cellular_automata::CellRow& CellularAutomataController::getCurrentGeneration() const noexcept {
	return automaton_->getCurrentGeneration();
}

cellular_automata::CellularAutomatonPtr CellularAutomataController::getCellularAutomaton() const noexcept {
	return automaton_;
}

}
