#pragma once

#include "cell_neighborhood_creator.h"
#include "k_nearest_neighbors_rule.h"
#include "type_definitions.h"

namespace cellular_automata {

class KNearestNeighborsCellNeighborhoodCreator : public CellNeighborhoodCreator {
public:
	KNearestNeighborsCellNeighborhoodCreator() = default;
	KNearestNeighborsCellNeighborhoodCreator(const RulePtr& rule, CellRow* row);

	virtual CellVector createCellNeighborhood(const CellVector::const_iterator& center) const override;

	virtual std::unique_ptr<CellNeighborhoodCreator> makeCopyFor(CellRow* row) const override;


private:
	void throwIfCenterIsCend(const CellVector::const_iterator& center) const;
	void throwIfRuleIsNotKnnRule() const;

	void calculateNeighborsLeftAndRightOfCenter() noexcept;

	integers::integer_t numberOfNeighborsLeftOfCenter_;
	integers::integer_t numberOfNeighborsRightOfCenter_;
	integers::integer_t numberOfNeighbors_;
};

}
