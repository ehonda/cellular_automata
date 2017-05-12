#pragma once

#include "cell_row_boundary_component.h"

namespace cellular_automata {

class BoundedCellRowBoundaryComponent
	: public CellRowBoundaryComponent {
public:
	using CellRowBoundaryComponent::CellRowBoundaryComponent;

	virtual Cell getCellBeforeFirstCellInRow(
		size_t distanceToFirst) override;
	virtual Cell getCellBeyondLastCellInRow(
		size_t distanceToLast) override;

	void setBoundaryCell(const Cell& cell);

private:
	Cell boundaryCell_;
};

}
