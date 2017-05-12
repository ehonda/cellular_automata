#pragma once

#include "base_b_integer.h"
#include "rule.h"
#include "type_definitions.h"

namespace cellular_automata
{

class KNearestNeighborsRule : public Rule
{
public:
	static const integers::integer_t MIN_NUMBER_OF_NEIGHBORS = 1;

	static KNearestNeighborsRulePtr createPtr(
		integers::BaseBInteger integerEncodedRule, integers::integer_t numberOfNeighbors);

	virtual Cell getNextGeneration(const CellNeighborhoodPtr& cellNeighborhood) const override;
	integers::integer_t getNumberOfNeighbors() const noexcept;

	virtual std::string toString() const override;

private:
	KNearestNeighborsRule(integers::BaseBInteger integerEncodedRule, integers::integer_t numberOfNeighbors);
	
	void throwIfInvalidNumberOfNeighbors() const;

	virtual bool equals(const Rule& other) const noexcept override;
	bool equalsOtherKnn(const KNearestNeighborsRule& other) const noexcept;

	integers::BaseBInteger _integerEncodedRule;
	integers::integer_t _numberOfNeighbors;
};

}
