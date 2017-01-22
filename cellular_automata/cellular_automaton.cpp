#include "cellular_automaton.h"

#include <stdexcept>

#include "cell_row.h"

namespace cellular_automata
{

CellularAutomaton::CellularAutomaton(CellRowPtr& initialGeneration)
	: _currentGeneration(std::move(initialGeneration))
{
	throwIfCellRowIsNullPtr();
	initializeCellRowPrototype(_currentGeneration);
	_nextGeneration = getCellRowFromPrototype();
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
	return CellRowPtr();
}

}
