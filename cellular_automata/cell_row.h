#pragma once

#include <memory>
#include <vector>

#include "cell.h"
#include "cell_neighborhood.h"

namespace cellular_automata
{

class CellRow
{
public:
	CellRow() = default;
	CellRow(const std::vector<Cell>& cells);

	virtual CellNeighborhoodPtr getNeighborhood(const std::vector<Cell>::const_iterator& center) const noexcept = 0;

protected:
	std::vector<Cell> _cells;
};

}