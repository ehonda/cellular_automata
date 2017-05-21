#include "cell_neighborhood_creator.h"

#include <cassert>

#include <stdexcept>

#include "rule.h"

namespace cellular_automata {

CellNeighborhoodCreator::CellNeighborhoodCreator(const RulePtr& rule, CellRow* row) 
	: rule_(rule), row_(row) {
	throwIfRuleIsNullPtr();
}

void CellNeighborhoodCreator::setRow(CellRow* row) {
	throwIfRuleIsNullPtr();
	row_ = row;
}

const RulePtr& CellNeighborhoodCreator::getRule() const noexcept {
	return rule_;
}

bool CellNeighborhoodCreator::operator==(const CellNeighborhoodCreator& other) const {
	return equals(other) && other.equals(*this);
}

bool CellNeighborhoodCreator::operator!=(const CellNeighborhoodCreator& other) const {
	return !operator==(other);
}

void CellNeighborhoodCreator::throwIfRuleIsNullPtr() const {
	if (!rule_)
		throw std::invalid_argument("Rule can not be set to nullptr for CellNeighborhoodCreator.");
}

bool CellNeighborhoodCreator::equals(const CellNeighborhoodCreator& other) const {
	assert(rule_);
	return *rule_ == *other.rule_;
}

}
