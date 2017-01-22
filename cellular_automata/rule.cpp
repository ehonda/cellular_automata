#include "rule.h"

#include <typeinfo>

namespace cellular_automata
{

Rule::Rule(integers::state_t numberOfStates) noexcept
	: _numberOfStates(numberOfStates)
{
}

integers::state_t Rule::getNumberOfStates() const noexcept
{
	return _numberOfStates;
}

bool Rule::operator==(const Rule& other) const noexcept
{
	if (typeid(*this) != typeid(other))
		return false;
	else
		return equals(other);
}

bool Rule::equals(const Rule& other) const noexcept
{
	return _numberOfStates == other._numberOfStates;
}

}
