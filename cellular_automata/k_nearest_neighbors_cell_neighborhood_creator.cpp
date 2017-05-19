#include "k_nearest_neighbors_cell_neighborhood_creator.h"

#include <cassert>

#include <stdexcept>

#include "cell_row.h"

namespace cellular_automata {

KNearestNeighborsCellNeighborhoodCreator::KNearestNeighborsCellNeighborhoodCreator(
	const RulePtr& rule, CellRow* row)
: CellNeighborhoodCreator(rule, row) {
	throwIfRuleIsNotKnnRule();
	calculateNeighborsLeftAndRightOfCenter();
}

CellVector KNearestNeighborsCellNeighborhoodCreator::createCellNeighborhood(const CellVector::const_iterator& center) const {
	throwIfCenterIsCend(center);
	CellVector cells(numberOfNeighbors_);

	size_t mid = numberOfNeighborsLeftOfCenter_;
	cells[mid] = *center;

	auto currentPos = center;
	bool outOfBounds = false;
	size_t distanceToFirst = 0;
	for (integers::integer_t i = 1; i <= numberOfNeighborsLeftOfCenter_; ++i) {
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
	for (integers::integer_t i = 1; i <= numberOfNeighborsRightOfCenter_; ++i) {
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

std::unique_ptr<CellNeighborhoodCreator> KNearestNeighborsCellNeighborhoodCreator::makeCopyFor(CellRow* row) const {
	std::unique_ptr<CellNeighborhoodCreator> copy(new KNearestNeighborsCellNeighborhoodCreator(*this));
	copy->setRow(row);
	return copy;
}

void KNearestNeighborsCellNeighborhoodCreator::throwIfCenterIsCend(const CellVector::const_iterator& center) const {
	if (center == row_->cend())
		throw std::invalid_argument("Centering KnnCellNeighborhoodCreator around cend of row is not possible.");
}

void KNearestNeighborsCellNeighborhoodCreator::throwIfRuleIsNotKnnRule() const {
	auto knnRule = dynamic_cast<const KNearestNeighborsRule*>(rule_.get());
	if (!knnRule)
		throw std::invalid_argument("Rule must be a K-Nearest-Neighbors Rule to instantiate KNearestNeighborsNeighborhoodCreator.");
}

void KNearestNeighborsCellNeighborhoodCreator::calculateNeighborsLeftAndRightOfCenter() noexcept {
	auto knnRule = static_cast<const KNearestNeighborsRule&>(*rule_);
	numberOfNeighbors_ = knnRule.getNumberOfNeighbors();

	auto numberOfNeighborsWithoutCenter = numberOfNeighbors_ - 1;
	numberOfNeighborsRightOfCenter_ = numberOfNeighborsWithoutCenter / 2;
	numberOfNeighborsLeftOfCenter_ = numberOfNeighborsWithoutCenter - numberOfNeighborsRightOfCenter_;
}

}
