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
	//Needed for polymorphism when copying CellRow
	virtual std::unique_ptr<CellRowBoundaryComponent> getPtrToCopy();
	//Better version for copying
	virtual std::unique_ptr<CellRowBoundaryComponent> makeCopyFor(
		CellRow* row);

protected:
	virtual bool equals(const CellRowBoundaryComponent& other) const override;
	bool equalsOtherBounded(const BoundedCellRowBoundaryComponent& other) const;

private:
	Cell boundaryCell_;
};

}
