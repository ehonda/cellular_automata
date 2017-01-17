#pragma once

#include "cell.h"
#include "cell_neighborhood.h"
#include "type_definitions.h"

namespace cellular_automata
{

class Rule
{
public:
	virtual Cell getNextGeneration(const CellNeighborhoodPtr& cellNeighborhood) const = 0;
	integers::state_t getNumberOfStates() const noexcept;

	virtual bool operator==(const Rule& other) const noexcept;

protected:
	Rule(integers::state_t numberOfStates);

	integers::state_t _numberOfStates;
};

}