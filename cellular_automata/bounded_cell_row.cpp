#include "bounded_cell_row.h"

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

CellVector::const_iterator BoundedCellRow::cbegin() const noexcept
{
	return ++_cells.cbegin();
}

CellVector::const_iterator BoundedCellRow::cend() const noexcept
{
	return --_cells.cend();
}

void BoundedCellRow::initializeCells(const CellVector& cells) noexcept
{
	_cells.emplace_back(_boundaryCell);
	for (const auto& cell : cells)
		_cells.emplace_back(cell);
	_cells.emplace_back(_boundaryCell);
}

}
