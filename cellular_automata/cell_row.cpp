#include "cell_row.h"

#include <stdexcept>

#include "cell_neighborhood.h"
#include "cell_neighborhood_creator.h"
#include "cell_neighborhood_creator_factory.h"

namespace cellular_automata
{

CellRow::CellRow(const CellVector& cells, const RulePtr& rule)
	: rule_(rule),
	_cells(cells),
	_cellNeighborhoodCreatorPtr(
		CellNeighborhoodCreatorFactory::getCreator(rule))
{
}

CellRow::CellRow(const RulePtr& rule)
	: rule_(rule),
	_cellNeighborhoodCreatorPtr(
		CellNeighborhoodCreatorFactory::getCreator(rule)) {
}

CellRow::CellRow(CellNeighborhoodCreatorPtr& cellNeighborhoodCreatorPtr)
	: _cellNeighborhoodCreatorPtr(std::move(cellNeighborhoodCreatorPtr))
{
	throwIfCellNeighborhoodCreatorIsNullPtr();
	rule_ = _cellNeighborhoodCreatorPtr->getRule();
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

CellVector::iterator CellRow::doBegin() noexcept
{
	return _cells.begin();
}

CellVector::iterator CellRow::doEnd() noexcept
{
	return _cells.end();
}

CellVector::const_iterator CellRow::doCbegin() const noexcept
{
	return _cells.cbegin();
}

CellVector::const_iterator CellRow::doCend() const noexcept
{
	return _cells.cend();
}

CellRowPtr CellRow::doGetPtrToCopy() const
{
	return CellRowPtr(new CellRow(_cells, rule_));
}

bool CellRow::equals(const CellRow& other) const
{
	return *_cellNeighborhoodCreatorPtr == *other._cellNeighborhoodCreatorPtr;
}

}
