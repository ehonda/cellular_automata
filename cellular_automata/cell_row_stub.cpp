#include "cell_row_stub.h"

namespace cellular_automata
{

CellRowStub::CellRowStub(CellNeighborhoodCreatorPtr& cellNeighborhoodCreatorPtr)
	: CellRow(cellNeighborhoodCreatorPtr)
{
}

CellVector::const_iterator CellRowStub::cbegin() const noexcept
{
	return CellVector::const_iterator();
}

CellVector::const_iterator CellRowStub::cend() const noexcept
{
	return CellVector::const_iterator();
}

}
