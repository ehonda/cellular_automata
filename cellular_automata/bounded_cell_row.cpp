//#include "bounded_cell_row.h"
//
//#include <memory>
//#include <stdexcept>
//
//#include "bounded_cell_row_boundary_component.h"
//#include "cell_neighborhood_creator.h"
//#include "k_nearest_neighbors_cell_neighborhood_creator.h"
//
//namespace cellular_automata
//{
//
////BoundedCellRow::BoundedCellRow(CellNeighborhoodCreatorPtr& cellNeighborhoodCreatorPtr,
////	const CellVector& cells)
////	: CellRow(cellNeighborhoodCreatorPtr)
////{
////	initializeCells(cells);
////}
//
//BoundedCellRow::BoundedCellRow(const KNearestNeighborsRulePtr& rule, const CellVector& cells) {
//	rule_ = rule;
//	boundaryComponent_ = std::unique_ptr<CellRowBoundaryComponent>(
//		new BoundedCellRowBoundaryComponent(this));
//	cellNeighborhoodCreator_ = std::make_unique<KNearestNeighborsCellNeighborhoodCreator>(rule);
//	initializeCells(cells);
//}
//
//const CellVector& BoundedCellRow::getCellsIncludingBoundaries() const noexcept
//{
//	return cells_;
//}
//
//void BoundedCellRow::setBoundaryCell(const Cell& boundaryCell) noexcept
//{
//	_boundaryCell = boundaryCell;
//	if (cells_.size() > 0)
//	{
//		/*auto rule = cellNeighborhoodCreator_->getRule();
//		auto knnRule = dynamic_cast<const KNearestNeighborsRule*>(rule.get());
//		if (!knnRule)
//			throw std::runtime_error("Rule could not be cast to knnRule (BoundedCellRow::padFrontBoundary)");
//		int halfNeighbors = knnRule->getNumberOfNeighbors() / 2;
//
//		for(int i = 0; i < halfNeighbors; ++i)
//			_cells[i] = _boundaryCell;
//
//		for(int i = 0; i < halfNeighbors; ++i)
//			_cells[_cells.size() - (halfNeighbors + 1) + i] = _boundaryCell;*/
//		cells_[0] = boundaryCell;
//		cells_[cells_.size() - 1] = boundaryCell;
//	}
//}
//
//void BoundedCellRow::padBoundary()
//{
//	auto rule = cellNeighborhoodCreator_->getRule();
//	auto knnRule = dynamic_cast<const KNearestNeighborsRule*>(rule.get());
//	if (!knnRule)
//		throw std::runtime_error("Rule could not be cast to knnRule (BoundedCellRow::padFrontBoundary)");
//	int halfNeighbors = knnRule->getNumberOfNeighbors() / 2;
//
//	for (int i = 0; i < halfNeighbors; ++i)
//		cells_.emplace_back(_boundaryCell);
//}
//
//void BoundedCellRow::initializeCells(const CellVector& cells)
//{
//	//padBoundary();
//	cells_.emplace_back(_boundaryCell);
//	for (const auto& cell : cells)
//		cells_.emplace_back(cell);
//	cells_.emplace_back(_boundaryCell);
//	//padBoundary();
//}
//
//CellVector::iterator BoundedCellRow::doBegin() noexcept
//{
//	return ++cells_.begin();
//}
//
//CellVector::iterator BoundedCellRow::doEnd() noexcept
//{
//	return --cells_.end();
//}
//
//CellVector::const_iterator BoundedCellRow::doCbegin() const noexcept
//{
//	return ++cells_.cbegin();
//}
//
//CellVector::const_iterator BoundedCellRow::doCend() const noexcept
//{
//	return --cells_.cend();
//}
//
//CellRowPtr BoundedCellRow::doGetPtrToCopy() const
//{
//	CellRowPtr ptrToCopy = std::make_unique<BoundedCellRow>(cellNeighborhoodCreator_->getPtrToCopy(), cells_);
//	static_cast<BoundedCellRow*>(ptrToCopy.get())->cells_ = cells_;
//	return ptrToCopy;
//}
//
//bool BoundedCellRow::equals(const CellRow& other) const
//{
//	bool equals = false;
//	auto otherBounded = dynamic_cast<const BoundedCellRow*>(&other);
//	if (otherBounded)
//		equals = equalsOtherBounded(*otherBounded);
//	return equals && CellRow::equals(other);
//}
//
//bool BoundedCellRow::equalsOtherBounded(const BoundedCellRow& other) const
//{
//	return cells_ == other.cells_
//		&& _boundaryCell == other._boundaryCell;
//}
//
//}
