#pragma once

//----------------------------------------------------------
//Obsolete? What is this stub for?
//----------------------------------------------------------

#include "cell_neighborhood_creator.h"

namespace cellular_automata
{

class CellNeighborhoodCreatorStub : public CellNeighborhoodCreator
{
public:
	using CellNeighborhoodCreator::CellNeighborhoodCreator;

	virtual CellVector createCellNeighborhood2(const CellVector::const_iterator& center) const override;

	virtual std::unique_ptr<CellNeighborhoodCreator> makeCopyFor(CellRow* row) const override;


private:
	virtual CellNeighborhoodPtr doCreateCellNeighborhood(const CellVector::const_iterator& center) const override;
	virtual CellNeighborhoodCreatorPtr doGetPtrToCopy() const noexcept override;
};

}
