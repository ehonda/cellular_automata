#include "cell_neighborhood_creator_stub.h"

#include "cell_neighborhood.h"

namespace cellular_automata
{

CellNeighborhoodPtr CellNeighborhoodCreatorStub::doCreateCellNeighborhood(const CellVector::const_iterator& center) const
{
	return CellNeighborhoodPtr();
}

CellNeighborhoodCreatorPtr CellNeighborhoodCreatorStub::doGetPtrToCopy() const noexcept
{
	return CellNeighborhoodCreatorPtr();
}

}