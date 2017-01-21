#include "rule.h"

#include <typeinfo>

namespace cellular_automata
{

integers::state_t Rule::getNumberOfStates() const noexcept
{
	return _numberOfStates;
}

bool Rule::operator==(const Rule& other) const noexcept
{
	if (typeid(*this) != typeid(other))
		return false;
	else
		return _numberOfStates == other._numberOfStates;
}

Rule::Rule(integers::state_t numberOfStates)
	: _numberOfStates(numberOfStates)
{
}

}
