#include "cell_row.h"

#include <stdexcept>
#include <typeinfo>

#include "cell_neighborhood.h"
#include "cell_neighborhood_creator.h"

namespace cellular_automata
{

CellRow::CellRow(CellNeighborhoodCreatorPtr& cellNeighborhoodCreatorPtr)
	: _cellNeighborhoodCreatorPtr(std::move(cellNeighborhoodCreatorPtr))
{
	throwIfCellNeighborhoodCreatorIsNullPtr();
}

CellNeighborhoodPtr CellRow::getNeighborhood(const CellVector::const_iterator& center) const
{
	return doGetNeighborhood(center);
}

CellVector::const_iterator CellRow::cbegin() const noexcept
{
	return doCbegin();
}

CellVector::const_iterator CellRow::cend() const noexcept
{
	return doCend();
}

CellRowPtr CellRow::getPtrToCopy() const
{
	return doGetPtrToCopy();
}

bool CellRow::operator==(const CellRow& other) const
{
	if (typeid(*this) != typeid(other))
		return false;
	else
		return equals(other);
}

bool CellRow::operator!=(const CellRow& other) const
{
	return !operator==(other);
}

void CellRow::throwIfCellNeighborhoodCreatorIsNullPtr() const
{
	if (!_cellNeighborhoodCreatorPtr)
		throw std::invalid_argument("CellNeighborhoodCreatorPtr is nullptr.");
}

CellNeighborhoodPtr CellRow::doGetNeighborhood(const CellVector::const_iterator& center) const
{
	return _cellNeighborhoodCreatorPtr->createCellNeighborhood(center);
}

bool CellRow::equals(const CellRow& other) const
{
	return *_cellNeighborhoodCreatorPtr == *other._cellNeighborhoodCreatorPtr;
}

}
