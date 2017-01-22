#pragma once

#include "type_definitions.h"

namespace cellular_automata
{

class CellularAutomaton
{
public:
	CellularAutomaton(CellRowPtr& initialGeneration);

private:
	void throwIfCellRowIsNullPtr() const;

	void initializeCellRowPrototype(const CellRowPtr& desiredCellRow) const;
	CellRowPtr getCellRowFromPrototype() const;

	mutable CellRowPtr _cellRowPrototype;
	CellRowPtr _currentGeneration;
	CellRowPtr _nextGeneration;
};

}
