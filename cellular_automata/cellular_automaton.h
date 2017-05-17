#pragma once

#include "cell_row.h"
#include "type_definitions.h"

namespace cellular_automata
{

class CellularAutomaton
{
public:
	CellularAutomaton() = default;
	//Obsolete
	CellularAutomaton(CellRowPtr& initialGeneration);
	//Obsolete
	CellularAutomaton(const KNearestNeighborsRulePtr& rule, const CellVector& initialGen);

	CellularAutomaton(const CellRow& initialGeneration);
	CellularAutomaton(const CellVector& initialCells, const RulePtr& rule);

	const CellRow& peekCurrentGeneration2() const noexcept;
	const CellRow& advanceToNextGeneration2();

	//Obsolete
	CellRowPtr peekCurrentGeneration() const;
	//Obsolete
	void advanceToNextGeneration();
	//Deprecated
	/*__declspec(deprecated)*/ CellRowPtr getNextGeneration();
	RulePtr getRule() const noexcept;

private:
	//Obsolete
	void throwIfCellRowIsNullPtr() const;
	//Obsolete
	void initializeCellRowPrototype(const CellRowPtr& desiredCellRow) const;
	//Obsolete
	CellRowPtr getCellRowFromPrototype() const;

	CellRow currentGeneration_;

	//Obsolete
	mutable CellRowPtr _cellRowPrototype;
	//Obsolete
	CellRowPtr _currentGeneration;
	//Obsolete
	CellRowPtr _nextGeneration;
	RulePtr _rule;
};

}
