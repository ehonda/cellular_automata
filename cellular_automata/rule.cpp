#include "rule.h"

namespace cellular_automata
{

Rule::Rule(integers::state_t numberOfStates) noexcept
	: numberOfStates_(numberOfStates)
{
}

integers::state_t Rule::getNumberOfStates() const noexcept
{
	return numberOfStates_;
}

bool Rule::operator==(const Rule& other) const noexcept
{
	return equals(other) && other.equals(*this);
}

bool Rule::operator!=(const Rule& other) const noexcept {
	return !operator==(other);
}

bool Rule::equals(const Rule& other) const noexcept
{
	return numberOfStates_ == other.numberOfStates_;
}

}
