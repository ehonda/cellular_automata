#pragma once

#include "cell.h"
#include "cell_row.h"
#include "type_definitions.h"

namespace cellular_automata
{

class BoundedCellRow : public CellRow
{
public:
	BoundedCellRow(CellNeighborhoodCreatorPtr& cellNeighborhoodCreatorPtr,
		const CellVector& cells);

	const CellVector& getCellsIncludingBoundaries() const noexcept;
	void setBoundaryCell(const Cell& boundaryCell) noexcept;

	virtual CellVector::const_iterator cbegin() const noexcept override;
	virtual CellVector::const_iterator cend() const noexcept override;

private:
	void initializeCells(const CellVector& cells) noexcept;

protected:
	CellVector _cells;
	Cell _boundaryCell;
};

}
