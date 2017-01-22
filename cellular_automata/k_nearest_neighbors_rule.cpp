#include "k_nearest_neighbors_rule.h"

#include <stdexcept>

namespace cellular_automata
{

KNearestNeighborsRulePtr KNearestNeighborsRule::createPtr(
	integers::BaseBInteger integerEncodedRule, integers::integer_t numberOfNeighbors)
{
	return KNearestNeighborsRulePtr(new KNearestNeighborsRule(integerEncodedRule, numberOfNeighbors));
}

Cell KNearestNeighborsRule::getNextGeneration(const CellNeighborhoodPtr& cellNeighborhood) const
{
	auto integerEncodedCellNeighborhood = cellNeighborhood->getIntegerEncodedCellNeighborhood();
	long index = integerEncodedCellNeighborhood.getInteger();
	integers::state_t nextState = _integerEncodedRule.getDigitAt(index);
	return Cell(nextState);
}

integers::integer_t KNearestNeighborsRule::getNumberOfNeighbors() const noexcept
{
	return _numberOfNeighbors;
}

KNearestNeighborsRule::KNearestNeighborsRule(integers::BaseBInteger integerEncodedRule, integers::integer_t numberOfNeighbors)
	: Rule(integerEncodedRule.getBase()), _integerEncodedRule(integerEncodedRule), _numberOfNeighbors(numberOfNeighbors)
{
	throwIfInvalidNumberOfNeighbors();
}

bool KNearestNeighborsRule::equals(const Rule& other) const noexcept
{
	auto knnOther = static_cast<const KNearestNeighborsRule&>(other);
	return Rule::equals(other)
		&& _numberOfNeighbors == knnOther._numberOfNeighbors
		&& _integerEncodedRule == knnOther._integerEncodedRule;
}

void KNearestNeighborsRule::throwIfInvalidNumberOfNeighbors() const
{
	if (_numberOfNeighbors < MIN_NUMBER_OF_NEIGHBORS)
		throw std::domain_error("The minimum number of neighbors was underrun");
}

}
