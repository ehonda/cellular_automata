#include "bounded_cell_row.h"

#include <memory>
#include <stdexcept>

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
{
	_cellNeighborhoodCreatorPtr = std::make_unique<KNearestNeighborsCellNeighborhoodCreator>(rule);
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
		/*auto rule = _cellNeighborhoodCreatorPtr->getRule();
		auto knnRule = dynamic_cast<const KNearestNeighborsRule*>(rule.get());
		if (!knnRule)
			throw std::runtime_error("Rule could not be cast to knnRule (BoundedCellRow::padFrontBoundary)");
		int halfNeighbors = knnRule->getNumberOfNeighbors() / 2;

		for(int i = 0; i < halfNeighbors; ++i)
			_cells[i] = _boundaryCell;

		for(int i = 0; i < halfNeighbors; ++i)
			_cells[_cells.size() - (halfNeighbors + 1) + i] = _boundaryCell;*/
		_cells[0] = boundaryCell;
		_cells[_cells.size() - 1] = boundaryCell;
	}
}

void BoundedCellRow::padBoundary()
{
	auto rule = _cellNeighborhoodCreatorPtr->getRule();
	auto knnRule = dynamic_cast<const KNearestNeighborsRule*>(rule.get());
	if (!knnRule)
		throw std::runtime_error("Rule could not be cast to knnRule (BoundedCellRow::padFrontBoundary)");
	int halfNeighbors = knnRule->getNumberOfNeighbors() / 2;

	for (int i = 0; i < halfNeighbors; ++i)
		_cells.emplace_back(_boundaryCell);
}

void BoundedCellRow::initializeCells(const CellVector& cells)
{
	//padBoundary();
	_cells.emplace_back(_boundaryCell);
	for (const auto& cell : cells)
		_cells.emplace_back(cell);
	_cells.emplace_back(_boundaryCell);
	//padBoundary();
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
