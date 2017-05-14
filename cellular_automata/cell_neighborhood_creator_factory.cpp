#include "cell_neighborhood_creator_factory.h"

#include <memory>
#include <stdexcept>

#include "k_nearest_neighbors_cell_neighborhood_creator.h"
#include "k_nearest_neighbors_rule.h"

namespace cellular_automata {

CellNeighborhoodCreatorPtr CellNeighborhoodCreatorFactory::getCreator(const RulePtr& rule, CellRow* row)
{
	CellNeighborhoodCreatorPtr creator;
	auto knnRule = std::dynamic_pointer_cast<KNearestNeighborsRule, Rule>(rule);
	if (knnRule)
		creator = CellNeighborhoodCreatorPtr(
			new KNearestNeighborsCellNeighborhoodCreator(knnRule, row));
	else
		throwOnUnkonwnRuleType();

	return creator;
}

void CellNeighborhoodCreatorFactory::throwOnUnkonwnRuleType() {
	throw std::invalid_argument("Unkown Ruletype for CellNeighborhoodCreator");
}

}
