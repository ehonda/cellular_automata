#pragma once

#include "gmpxx.h"

#include "base_b_integer.h"
#include "rule.h"
#include "type_definitions.h"

namespace cellular_automata {

class KNearestNeighborsRule : public Rule {
public:
	static const integers::state_t MIN_NUMBER_OF_STATES = 2;
	static const integers::integer_t MIN_NUMBER_OF_NEIGHBORS = 1;

	static KNearestNeighborsRulePtr createPtr(
		integers::BaseBInteger integerEncodedRule, integers::integer_t numberOfNeighbors);

	static mpz_class getNumberOfAutomataFor(unsigned long numberOfStates, unsigned long numberOfNeighbors);

	virtual Cell getNextGenerationForCenterCell(const CellVector& cellNeighborhood) const override;
	integers::integer_t getNumberOfNeighbors() const noexcept;

	virtual RulePtr getRandomRuleOfSameType() const override;

	virtual std::string toString() const override;

private:
	KNearestNeighborsRule(integers::BaseBInteger integerEncodedRule, integers::integer_t numberOfNeighbors);
	
	static void throwIfNumberOfStatesIsInvalid(integers::state_t numberOfStates);
	static void throwIfNumberOfNeighborsIsInvalid(integers::integer_t numberOfNeighbors);
	static void throwIfNumberOfPatternsIsTooBig(const mpz_class& numberOfPatterns);
	void throwIfInvalidNumberOfNeighbors() const;

	virtual bool equals(const Rule& other) const noexcept override;
	bool equalsOtherKnn(const KNearestNeighborsRule& other) const noexcept;

	integers::BaseBInteger _integerEncodedRule;
	integers::integer_t _numberOfNeighbors;
};

}
