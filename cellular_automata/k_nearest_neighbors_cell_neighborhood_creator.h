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

private:
	virtual void calculateNeighborsLeftAndRightOfCenter() const noexcept;

	virtual CellNeighborhoodPtr doCreateCellNeighborhood(const CellVector::const_iterator& center) const override;

	virtual CellNeighborhoodCreatorPtr doGetPtrToCopy() const noexcept override;

	mutable integers::integer_t _numberOfNeighborsLeftOfCenter;
	mutable integers::integer_t _numberOfNeighborsRightOfCenter;
};

}
