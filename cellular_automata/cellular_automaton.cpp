#include "cellular_automaton.h"

#include <stdexcept>

#include "bounded_cell_row.h"
#include "cell_row.h"
#include "rule.h"

namespace cellular_automata
{

CellularAutomaton::CellularAutomaton(CellRowPtr& initialGeneration)
	: _currentGeneration(std::move(initialGeneration))
{
	throwIfCellRowIsNullPtr();
	_rule = _currentGeneration->getRule();
	initializeCellRowPrototype(_currentGeneration);
	_nextGeneration = getCellRowFromPrototype();
}

CellularAutomaton::CellularAutomaton(const KNearestNeighborsRulePtr& rule, const CellVector& initialGen)
	: CellularAutomaton(CellRowPtr(new BoundedCellRow(rule, initialGen)))
{
}

CellRowPtr CellularAutomaton::peekCurrentGeneration() const
{
	return _currentGeneration->getPtrToCopy();
}

void CellularAutomaton::advanceToNextGeneration()
{
	_nextGeneration = getCellRowFromPrototype();
	auto nextGenIt = _nextGeneration->begin();

	for (auto currentGenIt = _currentGeneration->cbegin();
		currentGenIt != _currentGeneration->cend();
		++currentGenIt, ++nextGenIt) {
		auto neighborhood = _currentGeneration->getNeighborhood(currentGenIt);
		*nextGenIt = _rule->getNextGeneration(neighborhood);
	}

	_currentGeneration = _nextGeneration->getPtrToCopy();
}

CellRowPtr CellularAutomaton::getNextGeneration()
{
	advanceToNextGeneration();
	return _currentGeneration->getPtrToCopy();
}

RulePtr CellularAutomaton::getRule() const noexcept
{
	return _rule;
}

void CellularAutomaton::throwIfCellRowIsNullPtr() const
{
	if(!_currentGeneration)
		throw std::invalid_argument("initialGeneration is nullptr.");
}

void CellularAutomaton::initializeCellRowPrototype(const CellRowPtr& desiredCellRow) const
{
	_cellRowPrototype = desiredCellRow->getPtrToCopy();
}

CellRowPtr CellularAutomaton::getCellRowFromPrototype() const
{
	return _cellRowPrototype->getPtrToCopy();
}

}
