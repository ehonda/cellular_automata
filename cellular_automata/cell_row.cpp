#include "cell_row.h"

#include <stdexcept>

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

RulePtr CellRow::getRule() const
{
	return _cellNeighborhoodCreatorPtr->getRule();
}

CellVector::iterator CellRow::begin() noexcept
{
	return doBegin();
}

CellVector::iterator CellRow::end() noexcept
{
	return doEnd();
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
	return equals(other) && other.equals(*this);
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
