#include "cell_neighborhood_creator_factory.h"

#include <cassert>

#include <memory>
#include <stdexcept>

#include "k_nearest_neighbors_cell_neighborhood_creator.h"
#include "k_nearest_neighbors_rule.h"

namespace cellular_automata {

CellNeighborhoodCreatorPtr CellNeighborhoodCreatorFactory::getCreator(const RulePtr& rule, CellRow* row) {
	throwIfRuleIsNullPtr(rule);
	throwIfCellRowIsNullPtr(row);
	
	CellNeighborhoodCreatorPtr creator;
	auto knnRule = std::dynamic_pointer_cast<KNearestNeighborsRule, Rule>(rule);
	if (knnRule)
		creator = CellNeighborhoodCreatorPtr(
			new KNearestNeighborsCellNeighborhoodCreator(knnRule, row));
	else
		assert(false && "Unkown rule subclass can not be used to instantiate CellNeighborhoodCreator.");

	return creator;
}

void CellNeighborhoodCreatorFactory::throwIfRuleIsNullPtr(const RulePtr& rule) {
	if (!rule)
		throw std::invalid_argument("CellNeighborhoodCreator can not be instantiated for nullptr rule.");
}

void CellNeighborhoodCreatorFactory::throwIfCellRowIsNullPtr(CellRow* row) {
	if (row == nullptr)
		throw std::invalid_argument("CellNeighborhoodCreator can not be instantiated for nullptr row.");
}

}
