#include "bounded_cell_row.h"

#include "cell_neighborhood_creator.h"

namespace cellular_automata
{

BoundedCellRow::BoundedCellRow(CellNeighborhoodCreatorPtr& cellNeighborhoodCreatorPtr,
	const CellVector& cells)
	: CellRow(cellNeighborhoodCreatorPtr)
{
	initializeCells(cells);
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
	return CellRow::equals(other)
		&& _cells == static_cast<const BoundedCellRow&>(other)._cells
		&& _boundaryCell == static_cast<const BoundedCellRow&>(other)._boundaryCell;
}

}
