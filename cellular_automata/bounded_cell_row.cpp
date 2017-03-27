#include "bounded_cell_row.h"

#include "cell_neighborhood_creator.h"
#include "k_nearest_neighbors_cell_neighborhood_creator.h"

namespace cellular_automata
{

BoundedCellRow::BoundedCellRow(CellNeighborhoodCreatorPtr& cellNeighborhoodCreatorPtr,
	const CellVector& cells)
	: CellRow(cellNeighborhoodCreatorPtr)
{
	initializeCells(cells);
}

BoundedCellRow::BoundedCellRow(const KNearestNeighborsRulePtr& rule, const CellVector& cells)
	: CellRow(std::make_unique<KNearestNeighborsCellNeighborhoodCreator>(rule))
{
}


const CellVector& BoundedCellRow::getCellsIncludingBoundaries() const noexcept
{
	return _cells;
}

void BoundedCellRow::setBoundaryCell(const Cell& boundaryCell) noexcept
{
	_boundaryCell = boundaryCell;
	if (_cells.size() > 0)
	{
		_cells[0] = _boundaryCell;
		_cells[_cells.size() - 1] = _boundaryCell;
	}
}

void BoundedCellRow::initializeCells(const CellVector& cells)
{
	_cells.emplace_back(_boundaryCell);
	for (const auto& cell : cells)
		_cells.emplace_back(cell);
	_cells.emplace_back(_boundaryCell);
}

CellVector::iterator BoundedCellRow::doBegin() noexcept
{
	return ++_cells.begin();
}

CellVector::iterator BoundedCellRow::doEnd() noexcept
{
	return --_cells.end();
}

CellVector::const_iterator BoundedCellRow::doCbegin() const noexcept
{
	return ++_cells.cbegin();
}

CellVector::const_iterator BoundedCellRow::doCend() const noexcept
{
	return --_cells.cend();
}

CellRowPtr BoundedCellRow::doGetPtrToCopy() const
{
	CellRowPtr ptrToCopy = std::make_unique<BoundedCellRow>(_cellNeighborhoodCreatorPtr->getPtrToCopy(), _cells);
	static_cast<BoundedCellRow*>(ptrToCopy.get())->_cells = _cells;
	return ptrToCopy;
}

bool BoundedCellRow::equals(const CellRow& other) const
{
	bool equals = false;
	auto otherBounded = dynamic_cast<const BoundedCellRow*>(&other);
	if (otherBounded)
		equals = equalsOtherBounded(*otherBounded);
	return equals && CellRow::equals(other);
}

bool BoundedCellRow::equalsOtherBounded(const BoundedCellRow& other) const
{
	return _cells == other._cells
		&& _boundaryCell == other._boundaryCell;
}

}
