#include "k_nearest_neighbors_cell_neighborhood.h"

namespace cellular_automata
{

KNearestNeighborsCellNeighborhoodPtr KNearestNeighborsCellNeighborhood::createPtr(
	const CellVector& cells, const KNearestNeighborsRulePtr& rule)
{
	return KNearestNeighborsCellNeighborhoodPtr(new KNearestNeighborsCellNeighborhood(cells, rule));
}

const integers::BaseBInteger& KNearestNeighborsCellNeighborhood::getIntegerEncodedCellNeighborhood() const
{
	return _encodedCellNeighborhood;
}

bool KNearestNeighborsCellNeighborhood::operator==(const KNearestNeighborsCellNeighborhood& other) const noexcept
{
	return (_encodedCellNeighborhood == other._encodedCellNeighborhood) && (*_rule == *other._rule);
}

KNearestNeighborsCellNeighborhood::KNearestNeighborsCellNeighborhood(
	const CellVector& cells, const KNearestNeighborsRulePtr& rule)
	: _rule(rule)
{
	encodeCellNeighborhood(cells);
}

void KNearestNeighborsCellNeighborhood::encodeCellNeighborhood(const CellVector& cellNeighborhood)
{
	using namespace integers;

	BaseBInteger::BaseBRepresentation baseBRepresentation;
	for (const auto& cell : cellNeighborhood)
		baseBRepresentation.emplace_back(cell.getState());

	_encodedCellNeighborhood = BaseBInteger(_rule->getNumberOfStates(), baseBRepresentation);
}

}