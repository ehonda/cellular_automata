#include "cell_row.h"

namespace cellular_automata
{

CellRow::CellRow(CellNeighborhoodCreatorPtr& cellNeighborhoodCreatorPtr)
	: _cellNeighborhoodCreatorPtr(std::move(cellNeighborhoodCreatorPtr))
{
}

CellNeighborhoodPtr CellRow::getNeighborhood(const CellVector::const_iterator& center) const
{
	return doGetNeighborhood(center);
}

CellNeighborhoodPtr CellRow::doGetNeighborhood(const CellVector::const_iterator& center) const
{
	return _cellNeighborhoodCreatorPtr->createCellNeighborhood(center);
}

}
