#include "cell_row_stub.h"

namespace cellular_automata
{

CellVector::const_iterator CellRowStub::doCbegin() const noexcept
{
	return CellVector::const_iterator();
}

CellVector::const_iterator CellRowStub::doCend() const noexcept
{
	return CellVector::const_iterator();
}

CellRowPtr CellRowStub::doGetPtrToCopy() const
{
	return CellRowPtr();
}

}
