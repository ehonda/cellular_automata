#include "k_nearest_neighbors_rule.h"

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

bool KNearestNeighborsRule::operator==(const KNearestNeighborsRule& other) const noexcept
{
	return Rule::operator==(other)
		&& _numberOfNeighbors == other._numberOfNeighbors
		&& _integerEncodedRule == other._integerEncodedRule;
}

KNearestNeighborsRule::KNearestNeighborsRule(integers::BaseBInteger integerEncodedRule, integers::integer_t numberOfNeighbors)
	: Rule(integerEncodedRule.getBase()), _integerEncodedRule(integerEncodedRule), _numberOfNeighbors(numberOfNeighbors)
{
}

}