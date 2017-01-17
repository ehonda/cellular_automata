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

RuleStub::RuleStub(integers::state_t numberOfStates)
	: Rule(numberOfStates)
{
}

}