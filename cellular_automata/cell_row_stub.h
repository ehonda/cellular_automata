#pragma once

#include "cell_row.h"

namespace cellular_automata
{

class CellRowStub : public CellRow
{
public:
	using CellRow::CellRow;

private:
	virtual CellVector::iterator doBegin() noexcept override;
	virtual CellVector::iterator doEnd() noexcept override;
	virtual CellVector::const_iterator doCbegin() const noexcept override;
	virtual CellVector::const_iterator doCend() const noexcept override;
	virtual CellRowPtr doGetPtrToCopy() const override;
};

}