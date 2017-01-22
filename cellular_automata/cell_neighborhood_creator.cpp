#include "cell_neighborhood_creator.h"

#include <stdexcept>
#include <typeinfo>

#include "rule.h"

namespace cellular_automata
{

CellNeighborhoodCreator::CellNeighborhoodCreator(const RulePtr& rule)
	: _rule(rule)
{
	throwIfRuleIsNullPtr();
}

CellNeighborhoodPtr CellNeighborhoodCreator::createCellNeighborhood(const CellVector::const_iterator& center) const
{
	return doCreateCellNeighborhood(center);
}

const RulePtr& CellNeighborhoodCreator::getRule() const noexcept
{
	return _rule;
}

CellNeighborhoodCreatorPtr CellNeighborhoodCreator::getPtrToCopy() const noexcept
{
	return doGetPtrToCopy();
}

bool CellNeighborhoodCreator::operator==(const CellNeighborhoodCreator& other) const noexcept
{
	if (typeid(*this) != typeid(other))
		return false;
	else
		return equals(other);
}

bool CellNeighborhoodCreator::operator!=(const CellNeighborhoodCreator& other) const noexcept
{
	return !operator==(other);
}

void CellNeighborhoodCreator::throwIfRuleIsNullPtr() const
{
	if (!_rule)
		throw std::invalid_argument("Rule is nullptr.");
}

bool CellNeighborhoodCreator::equals(const CellNeighborhoodCreator& other) const noexcept
{
	return *_rule == *other._rule;
}

}
