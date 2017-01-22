#pragma once

#include "cell.h"
#include "cell_neighborhood.h"
#include "type_definitions.h"

namespace cellular_automata
{

class Rule
{
public:
	Rule(integers::state_t numberOfStates) noexcept;
	virtual ~Rule() = default;

	virtual Cell getNextGeneration(const CellNeighborhoodPtr& cellNeighborhood) const = 0;
	integers::state_t getNumberOfStates() const noexcept;

	bool operator==(const Rule& other) const noexcept;

protected:
	virtual bool equals(const Rule& other) const noexcept;

	integers::state_t _numberOfStates;
};

}
