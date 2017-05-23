#include "rule_stub.h"

namespace cellular_automata
{

std::unique_ptr<RuleStub> RuleStub::createPtr(integers::state_t numberOfStates)
{
	return std::unique_ptr<RuleStub>(new RuleStub(numberOfStates));
}

Cell RuleStub::getNextGenerationForCenterCell(const CellVector & cellNeighborhood) const
{
	return Cell();
}

RulePtr RuleStub::getRandomRuleOfSameType() const
{
	return RulePtr();
}

std::string RuleStub::toString() const
{
	return std::string();
}

RuleStub::RuleStub(integers::state_t numberOfStates)
	: Rule(numberOfStates)
{
}

}
