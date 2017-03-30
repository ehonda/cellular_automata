#pragma once

#include "type_definitions.h"

namespace cellular_automata
{

class CellularAutomaton
{
public:
	CellularAutomaton() = default;
	CellularAutomaton(CellRowPtr& initialGeneration);
	CellularAutomaton(const KNearestNeighborsRulePtr& rule, const CellVector& initialGen);

	CellRowPtr peekCurrentGeneration() const;
	void advanceToNextGeneration();
	/*__declspec(deprecated)*/ CellRowPtr getNextGeneration();

private:
	void throwIfCellRowIsNullPtr() const;

	void initializeCellRowPrototype(const CellRowPtr& desiredCellRow) const;
	CellRowPtr getCellRowFromPrototype() const;

	mutable CellRowPtr _cellRowPrototype;
	CellRowPtr _currentGeneration;
	CellRowPtr _nextGeneration;
	RulePtr _rule;
};

}
