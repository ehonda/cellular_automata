#include "k_nearest_neighbors_rule.h"

#include <chrono>
#include <stdexcept>

#include "base_converter.h"

namespace cellular_automata {

KNearestNeighborsRulePtr KNearestNeighborsRule::createPtr(
	integers::BaseBInteger integerEncodedRule, integers::integer_t numberOfNeighbors) {
	return KNearestNeighborsRulePtr(new KNearestNeighborsRule(integerEncodedRule, numberOfNeighbors));
}

mpz_class KNearestNeighborsRule::getNumberOfAutomataFor(unsigned long numberOfStates, unsigned long numberOfNeighbors)
{
	throwIfNumberOfStatesIsInvalid(numberOfStates);
	throwIfNumberOfNeighborsIsInvalid(numberOfNeighbors);

	mpz_class numberOfPatterns;
	mpz_ui_pow_ui(numberOfPatterns.get_mpz_t(), numberOfStates, numberOfNeighbors);
	throwIfNumberOfPatternsIsTooBig(numberOfPatterns);

	mpz_class numberOfAutomata;
	mpz_ui_pow_ui(numberOfAutomata.get_mpz_t(), numberOfStates, numberOfPatterns.get_ui());
	return numberOfAutomata;
}

Cell KNearestNeighborsRule::getNextGenerationForCenterCell(const CellVector& cellNeighborhood) const {
	integers::BaseConverter baseConverter(numberOfStates_);
	long index = baseConverter.getIntegerFromCellNeighborhood(cellNeighborhood);
	auto nextState = _integerEncodedRule.getDigitAt(index);
	return Cell(nextState);
}

integers::integer_t KNearestNeighborsRule::getNumberOfNeighbors() const noexcept {
	return _numberOfNeighbors;
}

RulePtr KNearestNeighborsRule::getRandomRuleOfSameType() const {
	gmp_randclass randClass{ gmp_randinit_default };
	unsigned long seed = static_cast<unsigned long>(
		std::chrono::system_clock::now().time_since_epoch().count());
	randClass.seed(seed);

	mpz_class numberOfAutomata = KNearestNeighborsRule::getNumberOfAutomataFor(numberOfStates_, _numberOfNeighbors);
	mpz_class randomInteger = randClass.get_z_range(numberOfAutomata);

	return KNearestNeighborsRule::createPtr(integers::BaseBInteger(numberOfStates_, randomInteger), _numberOfNeighbors);
}

std::string KNearestNeighborsRule::toString() const {
	return _integerEncodedRule.getInteger().get_str();
}

KNearestNeighborsRule::KNearestNeighborsRule(integers::BaseBInteger integerEncodedRule, integers::integer_t numberOfNeighbors)
	: Rule(integerEncodedRule.getBase()), _integerEncodedRule(integerEncodedRule), _numberOfNeighbors(numberOfNeighbors) {
	throwIfInvalidNumberOfNeighbors();
}

void KNearestNeighborsRule::throwIfNumberOfStatesIsInvalid(integers::state_t numberOfStates) {
	if (numberOfStates < MIN_NUMBER_OF_STATES)
		throw std::domain_error("The minimum number of states is " + std::to_string(MIN_NUMBER_OF_STATES));
}

void KNearestNeighborsRule::throwIfNumberOfNeighborsIsInvalid(integers::integer_t numberOfNeighbors) {
	if (numberOfNeighbors < MIN_NUMBER_OF_NEIGHBORS)
		throw std::domain_error("The minimum number of neighbors is " + std::to_string(MIN_NUMBER_OF_NEIGHBORS));
}

void KNearestNeighborsRule::throwIfNumberOfPatternsIsTooBig(const mpz_class& numberOfPatterns) {
	if (numberOfPatterns.fits_ulong_p() == 0)
		throw std::domain_error("The calculated number of patterns is too big.");
}

void KNearestNeighborsRule::throwIfInvalidNumberOfNeighbors() const {
	if (_numberOfNeighbors < MIN_NUMBER_OF_NEIGHBORS)
		throw std::domain_error("The minimum number of neighbors was underrun");
}

bool KNearestNeighborsRule::equalsOtherKnn(const KNearestNeighborsRule & other) const noexcept {
	return _numberOfNeighbors == other._numberOfNeighbors
		&& _integerEncodedRule == other._integerEncodedRule;
}

bool KNearestNeighborsRule::equals(const Rule& other) const noexcept {
	bool equals = false;
	auto otherKnn = dynamic_cast<const KNearestNeighborsRule*>(&other);
	if (otherKnn)
		equals = equalsOtherKnn(*otherKnn);
	return equals && Rule::equals(other);
}

}
