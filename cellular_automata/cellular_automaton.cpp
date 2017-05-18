#include "cellular_automaton.h"

#include "cell_row.h"
#include "rule.h"

namespace cellular_automata {

CellularAutomaton::CellularAutomaton(const CellRow& initialGeneration)
	: currentGeneration_(initialGeneration), rule_(initialGeneration.getRule()) {
}

CellularAutomaton::CellularAutomaton(const CellVector& initialCells, const RulePtr& rule)
	: CellularAutomaton(CellRow(initialCells, rule)) {
}

const CellRow& CellularAutomaton::getCurrentGeneration() const noexcept {
	return currentGeneration_;
}

const CellRow& CellularAutomaton::advanceToNextGeneration() {
	CellRow nextGeneration = currentGeneration_;
	auto nextGenIt = nextGeneration.begin();

	for (auto currentGenIt = currentGeneration_.cbegin();
		currentGenIt != currentGeneration_.cend();
		++currentGenIt, ++nextGenIt) 
	{
		auto neighborhood = currentGeneration_.getCellNeighborhood(currentGenIt);
		*nextGenIt = rule_->getNextGenerationForCenterCell(neighborhood);
	}

	currentGeneration_ = nextGeneration;
	return currentGeneration_;
}

const RulePtr& CellularAutomaton::getRule() const noexcept {
	return rule_;
}

}
