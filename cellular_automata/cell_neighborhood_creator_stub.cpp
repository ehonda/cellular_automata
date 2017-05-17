#include "cell_neighborhood_creator_stub.h"

#include "cell_neighborhood.h"

namespace cellular_automata
{
CellVector CellNeighborhoodCreatorStub::createCellNeighborhood2(const CellVector::const_iterator & center) const
{
	return CellVector();
}
std::unique_ptr<CellNeighborhoodCreator> CellNeighborhoodCreatorStub::makeCopyFor(CellRow * row) const
{
	return std::unique_ptr<CellNeighborhoodCreator>();
}
CellNeighborhoodPtr CellNeighborhoodCreatorStub::doCreateCellNeighborhood(const CellVector::const_iterator& center) const
{
	return CellNeighborhoodPtr();
}

CellNeighborhoodCreatorPtr CellNeighborhoodCreatorStub::doGetPtrToCopy() const noexcept
{
	return CellNeighborhoodCreatorPtr();
}

}