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

void BoundedCellRowBoundaryComponent::setBoundaryCell(
	const Cell& cell) {
	boundaryCell_ = cell;
}

}
