#include "cell_neighborhood_creator.h"

#include <cassert>

#include <stdexcept>

#include "rule.h"

namespace cellular_automata {

CellNeighborhoodCreator::CellNeighborhoodCreator(const RulePtr& rule, CellRow* row) 
	: rule_(rule), row_(row) {
	throwIfRuleIsNullPtr();
}

void CellNeighborhoodCreator::setRow(CellRow* row) noexcept {
	row_ = row;
}

const RulePtr& CellNeighborhoodCreator::getRule() const noexcept {
	return rule_;
}

std::unique_ptr<CellNeighborhoodCreator> CellNeighborhoodCreator::makeCopyFor(CellRow* row) const {
	return std::unique_ptr<CellNeighborhoodCreator>();
}

bool CellNeighborhoodCreator::operator==(const CellNeighborhoodCreator& other) const noexcept {
	return equals(other) && other.equals(*this);
}

bool CellNeighborhoodCreator::operator!=(const CellNeighborhoodCreator& other) const noexcept {
	return !operator==(other);
}

void CellNeighborhoodCreator::throwIfRuleIsNullPtr() const {
	if (!rule_)
		throw std::invalid_argument("Rule is nullptr.");
}

bool CellNeighborhoodCreator::equals(const CellNeighborhoodCreator& other) const noexcept {
	return *rule_ == *other.rule_;
}

}
