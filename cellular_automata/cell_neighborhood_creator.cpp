#include "cell_neighborhood_creator.h"

namespace cellular_automata
{

CellNeighborhoodCreator::CellNeighborhoodCreator(const RulePtr& rule)
	: _rule(rule)
{
}

const RulePtr& CellNeighborhoodCreator::getRule() const noexcept
{
	return _rule;
}

}
