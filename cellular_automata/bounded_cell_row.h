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

private:
	void initializeCells(const CellVector& cells);

	virtual CellVector::iterator doBegin() noexcept override;
	virtual CellVector::iterator doEnd() noexcept override;
	virtual CellVector::const_iterator doCbegin() const noexcept override;
	virtual CellVector::const_iterator doCend() const noexcept override;
	virtual CellRowPtr doGetPtrToCopy() const override;

protected:
	virtual bool equals(const CellRow& other) const override;
	bool equalsOtherBounded(const BoundedCellRow& other) const;

	CellVector _cells;
	Cell _boundaryCell;
};

}
