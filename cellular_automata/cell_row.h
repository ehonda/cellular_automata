#pragma once

#include <memory>

#include "cell.h"
#include "cell_neighborhood.h"
#include "cell_neighborhood_creator.h"
#include "type_definitions.h"

namespace cellular_automata
{

class CellRow
{
public:
	CellRow(CellNeighborhoodCreatorPtr& cellNeighborhoodCreatorPtr);
	virtual ~CellRow() = default;

	virtual CellNeighborhoodPtr getNeighborhood(const CellVector::const_iterator& center) const;
	virtual CellVector::const_iterator cbegin() const noexcept = 0;
	virtual CellVector::const_iterator cend() const noexcept = 0;

protected:
	CellNeighborhoodCreatorPtr _cellNeighborhoodCreatorPtr;
};

}
