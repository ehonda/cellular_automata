#pragma once

#include "base_b_integer.h"
#include "cell.h"
#include "rule.h"
#include "type_definitions.h"

namespace cellular_automata
{

class CellNeighborhood
{
public:
	static CellNeighborhoodPtr createPtr(const CellVector& cells, const RulePtr& rule);

	virtual const integers::BaseBInteger& getIntegerEncodedCellNeighborhood() const noexcept;
	virtual bool operator==(const CellNeighborhood& other) const noexcept;

private:
	CellNeighborhood(const CellVector& cells, const RulePtr& rule);
	void encodeCellNeighborhood(const CellVector& cells);

	integers::BaseBInteger _encodedCellNeighborhood;
	RulePtr _rule;
};

}