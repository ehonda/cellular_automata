#include "rule.h"

namespace cellular_automata
{

Rule::Rule(integers::state_t numberOfStates)
	: _numberOfStates(numberOfStates)
{
}

integers::state_t Rule::getNumberOfStates() const noexcept
{
	return _numberOfStates;
}

bool Rule::operator==(const Rule& other) const noexcept
{
	return _numberOfStates == other._numberOfStates;
}

}