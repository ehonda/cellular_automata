#include "k_nearest_neighbors_cell_neighborhood_creator.h"

#include <cmath>

namespace cellular_automata
{

KNearestNeighborsCellNeighborhoodCreator::KNearestNeighborsCellNeighborhoodCreator(const KNearestNeighborsRulePtr& rule)
	: CellNeighborhoodCreator(rule)
{
	calculateNeighborsLeftAndRightOfCenter();
}

void KNearestNeighborsCellNeighborhoodCreator::calculateNeighborsLeftAndRightOfCenter() const noexcept
{
	integers::integer_t numberOfNeighborsWithoutCenter =
		static_cast<const KNearestNeighborsRule&>(*_rule).getNumberOfNeighbors() - 1;
	_numberOfNeighborsRightOfCenter = numberOfNeighborsWithoutCenter / 2;
	_numberOfNeighborsLeftOfCenter = numberOfNeighborsWithoutCenter - _numberOfNeighborsRightOfCenter;
}

CellNeighborhoodPtr KNearestNeighborsCellNeighborhoodCreator::doCreateCellNeighborhood(const CellVector::const_iterator & center) const
{
	CellVector cells(static_cast<const KNearestNeighborsRule&>(*_rule).getNumberOfNeighbors());

	for (integers::integer_t i = 0; i < _numberOfNeighborsLeftOfCenter; ++i)
		cells[i] = *(center - (_numberOfNeighborsLeftOfCenter - i));

	cells[_numberOfNeighborsLeftOfCenter] = *center;

	for (integers::integer_t i = 0; i < _numberOfNeighborsRightOfCenter; ++i)
		cells[_numberOfNeighborsLeftOfCenter + 1 + i] = *(center + 1 + i);

	return CellNeighborhood::createPtr(cells, _rule);
}

CellNeighborhoodCreatorPtr KNearestNeighborsCellNeighborhoodCreator::doGetPtrToCopy() const noexcept
{
	return CellNeighborhoodCreatorPtr(
		new KNearestNeighborsCellNeighborhoodCreator(
			std::static_pointer_cast<KNearestNeighborsRule>(_rule)));
}

}
