#pragma once

#include "cell_neighborhood_creator.h"

namespace cellular_automata
{

class CellNeighborhoodCreatorStub : public CellNeighborhoodCreator
{
public:
	using CellNeighborhoodCreator::CellNeighborhoodCreator;

private:
	virtual CellNeighborhoodPtr doCreateCellNeighborhood(const CellVector::const_iterator& center) const override;
	virtual CellNeighborhoodCreatorPtr doGetPtrToCopy() const noexcept override;
};

}