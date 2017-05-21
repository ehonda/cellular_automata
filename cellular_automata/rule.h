#pragma once

#include <string>

#include "cell.h"
#include "cell_neighborhood.h"
#include "type_definitions.h"

namespace cellular_automata {

class Rule {
public:
	Rule(integers::state_t numberOfStates) noexcept;
	virtual ~Rule() = default;

	virtual Cell getNextGeneration(const CellNeighborhoodPtr& cellNeighborhood) const = 0;
	virtual Cell getNextGenerationForCenterCell(const CellVector& cellNeighborhood) const = 0;
	integers::state_t getNumberOfStates() const noexcept;

	virtual RulePtr getRandomRuleOfSameType() const = 0;

	bool operator==(const Rule& other) const noexcept;
	bool operator!=(const Rule& other) const noexcept;
	virtual std::string toString() const = 0;

protected:
	virtual bool equals(const Rule& other) const noexcept;

	integers::state_t numberOfStates_;
};

}
