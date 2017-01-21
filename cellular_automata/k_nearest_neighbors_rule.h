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

	virtual Cell getNextGeneration(const CellNeighborhoodPtr& cellNeighborhood) const;
	integers::integer_t getNumberOfNeighbors() const noexcept;

	virtual bool operator==(const Rule& other) const noexcept override;

private:
	KNearestNeighborsRule(integers::BaseBInteger integerEncodedRule, integers::integer_t numberOfNeighbors);
	virtual bool equals(const KNearestNeighborsRule& other) const noexcept;

	void throwIfInvalidNumberOfNeighbors() const;

	integers::BaseBInteger _integerEncodedRule;
	integers::integer_t _numberOfNeighbors;
};

}
