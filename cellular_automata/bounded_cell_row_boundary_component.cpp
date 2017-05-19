#include "bounded_cell_row_boundary_component.h"

namespace cellular_automata {

Cell BoundedCellRowBoundaryComponent::getCellBeforeFirstCellInRow(
	size_t distanceToFirst)
{
	return boundaryCell_;
}
Cell BoundedCellRowBoundaryComponent::getCellBeyondLastCellInRow(
	size_t distanceToLast)
{
	return boundaryCell_;
}

std::unique_ptr<CellRowBoundaryComponent> BoundedCellRowBoundaryComponent::makeCopyFor(CellRow* row)
{
	auto copy = std::unique_ptr<CellRowBoundaryComponent>(
		new BoundedCellRowBoundaryComponent(*this));
	copy->setCellRow(row);
	return copy;
}

bool BoundedCellRowBoundaryComponent::equals(const CellRowBoundaryComponent& other) const
{
	bool equals = false;
	auto otherBounded = dynamic_cast<const BoundedCellRowBoundaryComponent*>(&other);
	if (otherBounded)
		equals = equalsOtherBounded(*otherBounded);
	return equals;
}

bool BoundedCellRowBoundaryComponent::equalsOtherBounded(const BoundedCellRowBoundaryComponent& other) const {
	return boundaryCell_ == other.boundaryCell_;
}

void BoundedCellRowBoundaryComponent::setBoundaryCell(
	const Cell& cell) {
	boundaryCell_ = cell;
}

}
