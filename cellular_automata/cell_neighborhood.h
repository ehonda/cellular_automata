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
	virtual ~CellNeighborhood() = default;
	static CellNeighborhoodPtr createPtr(const CellVector& cells, const RulePtr& rule);

	const integers::BaseBInteger& getIntegerEncodedCellNeighborhood() const noexcept;
	bool operator==(const CellNeighborhood& other) const;

private:
	CellNeighborhood(const CellVector& cells, const RulePtr& rule);
	void encodeCellNeighborhood(const CellVector& cells);
	virtual bool equals(const CellNeighborhood& other) const;

	integers::BaseBInteger _encodedCellNeighborhood;
	RulePtr _rule;
};

}
