#pragma once

#include "cell_row.h"

namespace cellular_automata
{

class CellRowStub : public CellRow
{
public:
	CellRowStub(CellNeighborhoodCreatorPtr& cellNeighborhoodCreatorPtr);

	virtual CellVector::const_iterator cbegin() const noexcept override;
	virtual CellVector::const_iterator cend() const noexcept override;
};

}