#include "k_nearest_neighbors_cell_neighborhood_creator.h"

#include <cmath>

namespace cellular_automata
{

KNearestNeighborsCellNeighborhoodCreator::KNearestNeighborsCellNeighborhoodCreator(const KNearestNeighborsRulePtr& rule)
	: CellNeighborhoodCreator(rule)
{
	calculateNeighborsLeftAndRightOfCenter();
}

CellNeighborhoodPtr KNearestNeighborsCellNeighborhoodCreator::createCellNeighborhood(
	const CellVector::const_iterator& center) const noexcept
{
	CellVector cells(static_cast<const KNearestNeighborsRule&>(*_rule).getNumberOfNeighbors());

	for (integers::integer_t i = 0; i < _numberOfNeighborsLeftOfCenter; ++i)
		cells[i] = *(center - (_numberOfNeighborsLeftOfCenter - i));

	cells[_numberOfNeighborsLeftOfCenter] = *center;

	for (integers::integer_t i = 0; i < _numberOfNeighborsRightOfCenter; ++i)
		cells[_numberOfNeighborsLeftOfCenter + 1 + i] = *(center + 1 + i);

	return CellNeighborhood::createPtr(cells, _rule);
}

void KNearestNeighborsCellNeighborhoodCreator::calculateNeighborsLeftAndRightOfCenter() noexcept
{
	integers::integer_t numberOfNeighborsWithoutCenter =
		static_cast<const KNearestNeighborsRule&>(*_rule).getNumberOfNeighbors() - 1;
	_numberOfNeighborsRightOfCenter = numberOfNeighborsWithoutCenter / 2;
	_numberOfNeighborsLeftOfCenter = numberOfNeighborsWithoutCenter - _numberOfNeighborsRightOfCenter;
}

}
