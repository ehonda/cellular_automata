#include "cell_neighborhood_creator_factory.h"

#include <memory>

#include "k_nearest_neighbors_cell_neighborhood_creator.h"

namespace cellular_automata {

CellNeighborhoodCreatorPtr 
CellNeighborhoodCreatorFactory::getCreator(const RulePtr& rule)
{
	CellNeighborhoodCreatorPtr creator;
	/*
	KNearestNeighborsRulePtr knnRule = std::dynamic_pointer_cast<const RulePtr&>(rule);
	if (knnRule)
		creator = CellNeighborhoodCreatorPtr(new KNearestNeighborsCellNeighborhoodCreator(knnRule));

*/
	return CellNeighborhoodCreatorPtr();
}

}
