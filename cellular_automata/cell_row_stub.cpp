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

CellVector::iterator CellRowStub::doBegin() noexcept
{
	return CellVector::iterator();
}

CellVector::iterator CellRowStub::doEnd() noexcept
{
	return CellVector::iterator();
}

CellRowPtr CellRowStub::doGetPtrToCopy() const
{
	return CellRowPtr();
}

}
