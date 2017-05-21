#include "cell_row.h"

#include <stdexcept>

#include "bounded_cell_row_boundary_component.h"
#include "cell_neighborhood.h"
#include "cell_neighborhood_creator.h"
#include "cell_neighborhood_creator_factory.h"

namespace cellular_automata {

CellRow::CellRow(const CellVector& cells, const RulePtr& rule)
	:	cells_(cells),
		boundaryComponent_(new BoundedCellRowBoundaryComponent(this)),
		cellNeighborhoodCreator_(
		CellNeighborhoodCreatorFactory::getCreator(rule, this)) {
}

CellRow::CellRow(const CellRow& other)
	: cells_(other.cells_) {
	if (other.boundaryComponent_)
		boundaryComponent_ = other.boundaryComponent_->makeCopyFor(this);
	if (other.cellNeighborhoodCreator_)
		cellNeighborhoodCreator_ = other.cellNeighborhoodCreator_->makeCopyFor(this);
}

CellVector CellRow::getCellNeighborhood(const CellVector::const_iterator& center) const {
	throwIfCellNeighborhoodCreatorIsNullPtr();
	return cellNeighborhoodCreator_->createCellNeighborhood(center);
}

const CellVector& CellRow::getCells() const noexcept {
	return cells_;
}

RulePtr CellRow::getRule() const {
	throwIfCellNeighborhoodCreatorIsNullPtr();
	return cellNeighborhoodCreator_->getRule();
}

void CellRow::setBoundaryComponent(std::unique_ptr<CellRowBoundaryComponent>&& boundaryComponent) {
	boundaryComponent_ = std::move(boundaryComponent);
	boundaryComponent_->setCellRow(this);
}

const std::unique_ptr<CellRowBoundaryComponent>& CellRow::getBoundaryComponent() const noexcept {
	return boundaryComponent_;
}

CellVector::iterator CellRow::begin() noexcept {
	return cells_.begin();
}

CellVector::iterator CellRow::end() noexcept {
	return cells_.end();
}

CellVector::const_iterator CellRow::cbegin() const noexcept {
	return cells_.cbegin();
}

CellVector::const_iterator CellRow::cend() const noexcept {
	return cells_.cend();
}

CellRow& CellRow::operator=(const CellRow& other) {
	if (this != &other) {
		cells_ = other.cells_;
		if (other.cellNeighborhoodCreator_)
			cellNeighborhoodCreator_ = other.cellNeighborhoodCreator_->makeCopyFor(this);
		if (other.boundaryComponent_)
			boundaryComponent_ = other.boundaryComponent_->makeCopyFor(this);
	}
	return *this;
}

bool CellRow::operator==(const CellRow& other) const {
	bool equals = true;

	equals &= cells_ == other.cells_;

	if (boundaryComponent_ && other.boundaryComponent_)
		equals &= *boundaryComponent_ == *other.boundaryComponent_;
	else if (!boundaryComponent_ && !other.boundaryComponent_)
		equals &= true;
	else
		equals &= false;

	if (cellNeighborhoodCreator_ && other.cellNeighborhoodCreator_)
		equals &= *cellNeighborhoodCreator_ == *other.cellNeighborhoodCreator_;
	else if (!cellNeighborhoodCreator_ && !other.cellNeighborhoodCreator_)
		equals &= true;
	else
		equals &= false;

	return equals;
}

bool CellRow::operator!=(const CellRow& other) const {
	return !operator==(other);
}

void CellRow::throwIfCellNeighborhoodCreatorIsNullPtr() const {
	if (!cellNeighborhoodCreator_)
		throw std::logic_error("Attempting to dereference uninitialised cellNeighborhoodCreator.");
}

}
