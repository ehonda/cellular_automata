#pragma once

#include "cell_neighborhood_creator.h"
#include "k_nearest_neighbors_rule.h"
#include "type_definitions.h"

namespace cellular_automata
{

class KNearestNeighborsCellNeighborhoodCreator : public CellNeighborhoodCreator
{
public:
	KNearestNeighborsCellNeighborhoodCreator(const KNearestNeighborsRulePtr& rule);

	virtual CellNeighborhoodPtr createCellNeighborhood(const CellVector::const_iterator& center) const noexcept override;

private:
	void calculateNeighborsLeftAndRightOfCenter() noexcept;

	KNearestNeighborsRulePtr _rule;
	integers::integer_t _numberOfNeighborsLeftOfCenter;
	integers::integer_t _numberOfNeighborsRightOfCenter;
};

}
