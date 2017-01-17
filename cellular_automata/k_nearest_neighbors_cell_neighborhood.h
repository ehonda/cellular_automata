#pragma once

#include <vector>

#include "cell_neighborhood.h"
#include "k_nearest_neighbors_rule.h"
#include "type_definitions.h"

namespace cellular_automata
{

class KNearestNeighborsCellNeighborhood : public CellNeighborhood
{
public:
	static KNearestNeighborsCellNeighborhoodPtr createPtr(const CellVector& cells, const KNearestNeighborsRulePtr& rule);

	virtual const integers::BaseBInteger& getIntegerEncodedCellNeighborhood() const;

	virtual bool operator==(const KNearestNeighborsCellNeighborhood& other) const noexcept;

private:
	KNearestNeighborsCellNeighborhood(const CellVector& cells, const KNearestNeighborsRulePtr& rule);
	void encodeCellNeighborhood(const CellVector& cellNeighborhood);

	integers::BaseBInteger _encodedCellNeighborhood;
	KNearestNeighborsRulePtr _rule;
};

}