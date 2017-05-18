#pragma once

#include "cell_row.h"
#include "type_definitions.h"

namespace cellular_automata {

class CellularAutomaton {
public:
	CellularAutomaton() = default;
	CellularAutomaton(const CellRow& initialGeneration);
	CellularAutomaton(const CellVector& initialCells, const RulePtr& rule);

	const CellRow& getCurrentGeneration() const noexcept;
	const CellRow& advanceToNextGeneration();

	const RulePtr& getRule() const noexcept;

private:
	CellRow currentGeneration_;
	RulePtr rule_;
};

}
