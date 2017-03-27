#pragma once

#include "rule.h"
#include "k_nearest_neighbors_rule.h"
#include "type_definitions.h"

namespace cellular_automata_test {

using namespace cellular_automata;

class BasicRules {
public:
	static KNearestNeighborsRulePtr getRule30() {
		integers::BaseBInteger ruleEncoded(2, 30);
		size_t neighbors = 3;
		return KNearestNeighborsRule::createPtr(ruleEncoded, neighbors);
	}
};

}
