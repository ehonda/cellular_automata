#include "cellular_automata_controller.h"

namespace cellular_automata_mvc {

CellularAutomataController::CellularAutomataController(
	const cellular_automata::KNearestNeighborsRulePtr& rule,
	const cellular_automata::CellVector& initialCells)
{
	automaton_ = std::make_shared<cellular_automata::CellularAutomaton>(rule, initialCells);
}

void CellularAutomataController::iterate()
{
	automaton_->advanceToNextGeneration();
}

cellular_automata::CellRowPtr CellularAutomataController::getCurrentGeneration() const
{
	return automaton_->peekCurrentGeneration();
}

cellular_automata::CellularAutomatonPtr CellularAutomataController::getCellularAutomaton() const
{
	return automaton_;
}

}
