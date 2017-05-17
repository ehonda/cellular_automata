#include "rule_stub.h"

namespace cellular_automata
{

std::unique_ptr<RuleStub> RuleStub::createPtr(integers::state_t numberOfStates)
{
	return std::unique_ptr<RuleStub>(new RuleStub(numberOfStates));
}

Cell RuleStub::getNextGeneration(const CellNeighborhoodPtr& cellNeighborhood) const
{
	return Cell();
}

Cell RuleStub::getNextGenerationForCenterCell(const CellVector & cellNeighborhood) const
{
	return Cell();
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
