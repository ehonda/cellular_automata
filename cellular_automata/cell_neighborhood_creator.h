#pragma once

#include <vector>

#include "cell.h"
#include "cell_neighborhood.h"
#include "type_definitions.h"

namespace cellular_automata
{

class CellNeighborhoodCreator
{
public:
	CellNeighborhoodCreator(const RulePtr& rule);
	virtual ~CellNeighborhoodCreator() = default;

	const RulePtr& getRule() const noexcept;
	virtual CellNeighborhoodPtr createCellNeighborhood(const CellVector::const_iterator& center) const noexcept = 0;

protected:
	RulePtr _rule;
};

}
