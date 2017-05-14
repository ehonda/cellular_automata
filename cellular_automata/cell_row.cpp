#include "cell_row.h"

#include <stdexcept>

#include "bounded_cell_row_boundary_component.h"
#include "cell_neighborhood.h"
#include "cell_neighborhood_creator.h"
#include "cell_neighborhood_creator_factory.h"

namespace cellular_automata
{

CellRow::CellRow(const CellVector& cells, const RulePtr& rule)
	: rule_(rule),
	cells_(cells),
	boundaryComponent_(new BoundedCellRowBoundaryComponent(this)),
	cellNeighborhoodCreator_(
		CellNeighborhoodCreatorFactory::getCreator(rule, this)) {
}

CellRow::CellRow(const RulePtr& rule)
	: rule_(rule),
	boundaryComponent_(new BoundedCellRowBoundaryComponent(this)),
	cellNeighborhoodCreator_(
		CellNeighborhoodCreatorFactory::getCreator(rule, this)) {
}

CellRow::CellRow(CellNeighborhoodCreatorPtr& cellNeighborhoodCreatorPtr)
	: boundaryComponent_(new BoundedCellRowBoundaryComponent(this)), 
	cellNeighborhoodCreator_(std::move(cellNeighborhoodCreatorPtr))
{
	throwIfCellNeighborhoodCreatorIsNullPtr();
	rule_ = cellNeighborhoodCreator_->getRule();
}

CellRow::CellRow(const CellRow& other)
	: CellRow(other.cells_, other.rule_)
{
	if (other.boundaryComponent_) {
		boundaryComponent_ = other.boundaryComponent_->getPtrToCopy();
		boundaryComponent_->setCellRow(this);
	}
}

CellNeighborhoodPtr CellRow::getNeighborhood(const CellVector::const_iterator& center) const
{
	return doGetNeighborhood(center);
}

CellVector CellRow::getCellNeighborhood(const CellVector::const_iterator& center) const
{
	return cellNeighborhoodCreator_->createCellNeighborhood2(center);
}

RulePtr CellRow::getRule() const
{
	return cellNeighborhoodCreator_->getRule();
}

void CellRow::setBoundaryComponent(std::unique_ptr<CellRowBoundaryComponent>&& boundaryComponent) {
	boundaryComponent_ = std::move(boundaryComponent);
	boundaryComponent_->setCellRow(this);
}

const std::unique_ptr<CellRowBoundaryComponent>& CellRow::getBoundaryComponent() const noexcept {
	return boundaryComponent_;
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

CellRow& CellRow::operator=(const CellRow& other)
{
	if (this != &other) {
		rule_ = other.rule_;
		cells_ = other.cells_;
		cellNeighborhoodCreator_ =
			CellNeighborhoodCreatorFactory::getCreator(rule_, this);
		if (other.boundaryComponent_) {
			boundaryComponent_ = other.boundaryComponent_->getPtrToCopy();
			boundaryComponent_->setCellRow(this);
		}
	}
	return *this;
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
	if (!cellNeighborhoodCreator_)
		throw std::invalid_argument("CellNeighborhoodCreatorPtr is nullptr.");
}

CellNeighborhoodPtr CellRow::doGetNeighborhood(const CellVector::const_iterator& center) const
{
	return cellNeighborhoodCreator_->createCellNeighborhood(center);
}

CellVector::iterator CellRow::doBegin() noexcept
{
	return cells_.begin();
}

CellVector::iterator CellRow::doEnd() noexcept
{
	return cells_.end();
}

CellVector::const_iterator CellRow::doCbegin() const noexcept
{
	return cells_.cbegin();
}

CellVector::const_iterator CellRow::doCend() const noexcept
{
	return cells_.cend();
}

CellRowPtr CellRow::doGetPtrToCopy() const
{
	auto copy = CellRowPtr(new CellRow(cells_, rule_));
	if (boundaryComponent_) {
		copy->boundaryComponent_ = boundaryComponent_->getPtrToCopy();
		copy->boundaryComponent_->setCellRow(copy.get());
	}
	return copy;
}

bool CellRow::equals(const CellRow& other) const
{
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

}
