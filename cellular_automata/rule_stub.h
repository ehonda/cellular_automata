#pragma once

#include <memory>

#include "rule.h"
#include "type_definitions.h"

namespace cellular_automata
{

class RuleStub : public Rule
{
public:
	static std::unique_ptr<RuleStub> createPtr(integers::state_t numberOfStates);

	virtual Cell getNextGeneration(const CellNeighborhoodPtr& cellNeighborhood) const override;
	virtual Cell getNextGenerationForCenterCell(const CellVector& cellNeighborhood) const override;

	virtual std::string toString() const override;

private:
	RuleStub(integers::state_t numberOfStates);
};

}
