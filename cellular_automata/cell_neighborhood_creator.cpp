#include "cell_neighborhood_creator.h"

#include <stdexcept>

#include "rule.h"

namespace cellular_automata
{

CellNeighborhoodCreator::CellNeighborhoodCreator(const RulePtr& rule)
	: _rule(rule)
{
	throwIfRuleIsNullPtr();
}

CellNeighborhoodCreator::CellNeighborhoodCreator(const RulePtr& rule, CellRow* row) 
	: _rule(rule), row_(row) {
	throwIfRuleIsNullPtr();
}

CellNeighborhoodPtr CellNeighborhoodCreator::createCellNeighborhood(const CellVector::const_iterator& center) const
{
	return doCreateCellNeighborhood(center);
}

void CellNeighborhoodCreator::setRow(CellRow* row) noexcept {
	row_ = row;
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
	return equals(other) && other.equals(*this);
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
