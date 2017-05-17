#include "k_nearest_neighbors_cell_neighborhood_creator.h"

#include <cassert>
#include <cmath>

#include <stdexcept>

#include "cell_row.h"

namespace cellular_automata
{

KNearestNeighborsCellNeighborhoodCreator::KNearestNeighborsCellNeighborhoodCreator(
	const RulePtr& rule, CellRow* row)
: CellNeighborhoodCreator(rule, row) {
	throwIfRuleIsNotKnnRule();
	calculateNeighborsLeftAndRightOfCenter();
}

KNearestNeighborsCellNeighborhoodCreator::KNearestNeighborsCellNeighborhoodCreator(const KNearestNeighborsRulePtr& rule)
	: CellNeighborhoodCreator(rule)
{
	calculateNeighborsLeftAndRightOfCenter();
}

CellVector KNearestNeighborsCellNeighborhoodCreator::createCellNeighborhood2(const CellVector::const_iterator& center) const
{
	assert(center != row_->cend());
	CellVector cells(numberOfNeighbors_);

	size_t mid = _numberOfNeighborsLeftOfCenter;
	cells[mid] = *center;

	auto currentPos = center;
	bool outOfBounds = false;
	size_t distanceToFirst = 0;
	for (integers::integer_t i = 1; i <= _numberOfNeighborsLeftOfCenter; ++i) {
		if (outOfBounds) {
			//++distanceToFirst might be off by 1 here, it doesnt matter as long as only bounded cell rows are used
			cells[mid - i] = row_->getBoundaryComponent()->getCellBeforeFirstCellInRow(++distanceToFirst);
		}
		else {
			if (currentPos == row_->cbegin()) {
				outOfBounds = true;
				//Decrease i, else "this" step wont insert a value into cells
				--i;
			}
			else {
				currentPos = center - i;
				cells[mid - i] = *currentPos;
			}
		}
	}

	outOfBounds = false;
	size_t distanceToLast = 0;
	for (integers::integer_t i = 1; i <= _numberOfNeighborsRightOfCenter; ++i) {
		if (outOfBounds) {
			cells[mid + i] = row_->getBoundaryComponent()->getCellBeyondLastCellInRow(++distanceToLast);
		}
		else {
			currentPos = center + i;
			if (currentPos == row_->cend()) {
				outOfBounds = true;
				//Decrease i, else "this" step wont insert a value into cells
				--i;
			}
			else {
				cells[mid + i] = *currentPos;
			}
		}
	}

	return cells;
}

std::unique_ptr<CellNeighborhoodCreator> KNearestNeighborsCellNeighborhoodCreator::makeCopyFor(CellRow* row) const
{
	std::unique_ptr<CellNeighborhoodCreator> copy(new KNearestNeighborsCellNeighborhoodCreator(*this));
	copy->setRow(row);
	return copy;
}

void KNearestNeighborsCellNeighborhoodCreator::throwIfRuleIsNotKnnRule() const {
	auto knnRule = dynamic_cast<const KNearestNeighborsRule*>(_rule.get());
	if (!knnRule)
		throw std::invalid_argument("Rule must be a K-Nearest-Neighbors Rule to instantiate KNearestNeighborsNeighborhoodCreator.");
}

void KNearestNeighborsCellNeighborhoodCreator::calculateNeighborsLeftAndRightOfCenter() const noexcept
{
	auto knnRule = static_cast<const KNearestNeighborsRule&>(*_rule);
	numberOfNeighbors_ = knnRule.getNumberOfNeighbors();
	integers::integer_t numberOfNeighborsWithoutCenter = numberOfNeighbors_ - 1;
	_numberOfNeighborsRightOfCenter = numberOfNeighborsWithoutCenter / 2;
	_numberOfNeighborsLeftOfCenter = numberOfNeighborsWithoutCenter - _numberOfNeighborsRightOfCenter;
}

CellNeighborhoodPtr KNearestNeighborsCellNeighborhoodCreator::doCreateCellNeighborhood(const CellVector::const_iterator & center) const
{
	CellVector cells(static_cast<const KNearestNeighborsRule&>(*_rule).getNumberOfNeighbors());

	for (integers::integer_t i = 0; i < _numberOfNeighborsLeftOfCenter; ++i)
		cells[i] = *(center - (_numberOfNeighborsLeftOfCenter - i));

	cells[_numberOfNeighborsLeftOfCenter] = *center;

	for (integers::integer_t i = 0; i < _numberOfNeighborsRightOfCenter; ++i)
		cells[_numberOfNeighborsLeftOfCenter + 1 + i] = *(center + 1 + i);

	return CellNeighborhood::createPtr(cells, _rule);
}

CellNeighborhoodCreatorPtr KNearestNeighborsCellNeighborhoodCreator::doGetPtrToCopy() const noexcept
{
	return CellNeighborhoodCreatorPtr(
		new KNearestNeighborsCellNeighborhoodCreator(
			std::static_pointer_cast<KNearestNeighborsRule>(_rule)));
}

}
