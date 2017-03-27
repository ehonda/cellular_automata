#pragma once

#include "type_definitions.h"

namespace cellular_automata
{

class CellRow
{
public:
	CellRow(CellNeighborhoodCreatorPtr& cellNeighborhoodCreatorPtr);
	virtual ~CellRow() = default;

	CellNeighborhoodPtr getNeighborhood(const CellVector::const_iterator& center) const;
	RulePtr getRule() const;
	CellVector::iterator begin() noexcept;
	CellVector::iterator end() noexcept;
	CellVector::const_iterator cbegin() const noexcept;
	CellVector::const_iterator cend() const noexcept;

	CellRowPtr getPtrToCopy() const;
	bool operator==(const CellRow& other) const;
	bool operator!=(const CellRow& other) const;

private:
	void throwIfCellNeighborhoodCreatorIsNullPtr() const;

	virtual CellNeighborhoodPtr doGetNeighborhood(const CellVector::const_iterator& center) const;
	virtual CellVector::iterator doBegin() noexcept = 0;
	virtual CellVector::iterator doEnd() noexcept = 0;
	virtual CellVector::const_iterator doCbegin() const noexcept = 0;
	virtual CellVector::const_iterator doCend() const noexcept = 0;
	virtual CellRowPtr doGetPtrToCopy() const = 0;

protected:
	CellRow() = default;
	virtual bool equals(const CellRow& other) const;

	CellNeighborhoodCreatorPtr _cellNeighborhoodCreatorPtr;
};

}
