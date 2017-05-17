#pragma once

#include "cell_neighborhood_creator.h"
#include "k_nearest_neighbors_rule.h"
#include "type_definitions.h"

namespace cellular_automata
{

class KNearestNeighborsCellNeighborhoodCreator : public CellNeighborhoodCreator
{
public:
	KNearestNeighborsCellNeighborhoodCreator() = default;
	KNearestNeighborsCellNeighborhoodCreator(const RulePtr& rule, CellRow* row);
	KNearestNeighborsCellNeighborhoodCreator(const KNearestNeighborsRulePtr& rule);

	virtual CellVector createCellNeighborhood2(const CellVector::const_iterator& center) const override;

	virtual std::unique_ptr<CellNeighborhoodCreator> makeCopyFor(CellRow* row) const override;


private:
	void throwIfRuleIsNotKnnRule() const;

	virtual void calculateNeighborsLeftAndRightOfCenter() const noexcept;

	virtual CellNeighborhoodPtr doCreateCellNeighborhood(const CellVector::const_iterator& center) const override;

	virtual CellNeighborhoodCreatorPtr doGetPtrToCopy() const noexcept override;

	mutable integers::integer_t _numberOfNeighborsLeftOfCenter;
	mutable integers::integer_t _numberOfNeighborsRightOfCenter;
	mutable integers::integer_t numberOfNeighbors_;
};

}
