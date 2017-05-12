#pragma once

#include "type_definitions.h"

namespace cellular_automata
{

class CellRow
{
public:
	CellRow(const CellVector& cells, const RulePtr& rule);
	CellRow(const RulePtr& rule);
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
	virtual CellVector::iterator doBegin() noexcept;
	virtual CellVector::iterator doEnd() noexcept;
	virtual CellVector::const_iterator doCbegin() const noexcept;
	virtual CellVector::const_iterator doCend() const noexcept;
	virtual CellRowPtr doGetPtrToCopy() const;

protected:
	CellRow() = default;
	virtual bool equals(const CellRow& other) const;

	RulePtr rule_;
	CellVector _cells;
	CellNeighborhoodCreatorPtr _cellNeighborhoodCreatorPtr;
};

}
