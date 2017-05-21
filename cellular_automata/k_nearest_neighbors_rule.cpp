#include "k_nearest_neighbors_rule.h"

#include <cmath>

#include <chrono>
#include <random>
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

Cell KNearestNeighborsRule::getNextGenerationForCenterCell(const CellVector& cellNeighborhood) const {
	auto integerEncodedCellNeighborhood = integers::BaseBInteger(numberOfStates_, cellNeighborhood);
	long index = integerEncodedCellNeighborhood.getInteger();
	integers::state_t nextState = _integerEncodedRule.getDigitAt(index);
	return Cell(nextState);
}

integers::integer_t KNearestNeighborsRule::getNumberOfNeighbors() const noexcept
{
	return _numberOfNeighbors;
}

RulePtr KNearestNeighborsRule::getRandomRuleOfSameType() const {
	unsigned seed = static_cast<unsigned>(
		std::chrono::system_clock::now().time_since_epoch().count());
	std::mt19937 gen(seed);

	long double longStates = static_cast<long double>(numberOfStates_);
	long double longNeighbors = static_cast<long double>(_numberOfNeighbors);
	long long numberOfAutomata = static_cast<long long>(pow(longStates, pow(longStates, longNeighbors)));

	long upperBound = 0;
	if (numberOfAutomata > LONG_MAX || numberOfAutomata < 0LL)
		upperBound = LONG_MAX;
	else
		upperBound = static_cast<long>(numberOfAutomata);

	std::uniform_int_distribution<long> dist(0, upperBound);

	auto integerRep = dist(gen);
	return KNearestNeighborsRule::createPtr(
		integers::BaseBInteger(numberOfStates_, integerRep),
		_numberOfNeighbors);
}

std::string KNearestNeighborsRule::toString() const
{
	return std::to_string(_integerEncodedRule.getInteger());
}

KNearestNeighborsRule::KNearestNeighborsRule(integers::BaseBInteger integerEncodedRule, integers::integer_t numberOfNeighbors)
	: Rule(integerEncodedRule.getBase()), _integerEncodedRule(integerEncodedRule), _numberOfNeighbors(numberOfNeighbors)
{
	throwIfInvalidNumberOfNeighbors();
}

void KNearestNeighborsRule::throwIfInvalidNumberOfNeighbors() const
{
	if (_numberOfNeighbors < MIN_NUMBER_OF_NEIGHBORS)
		throw std::domain_error("The minimum number of neighbors was underrun");
}

bool KNearestNeighborsRule::equalsOtherKnn(const KNearestNeighborsRule & other) const noexcept
{
	return _numberOfNeighbors == other._numberOfNeighbors
		&& _integerEncodedRule == other._integerEncodedRule;
}

bool KNearestNeighborsRule::equals(const Rule& other) const noexcept
{
	bool equals = false;
	auto otherKnn = dynamic_cast<const KNearestNeighborsRule*>(&other);
	if (otherKnn)
		equals = equalsOtherKnn(*otherKnn);
	return equals && Rule::equals(other);
}

}
