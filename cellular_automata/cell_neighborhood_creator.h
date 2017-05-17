#pragma once

#include "type_definitions.h"

namespace cellular_automata
{

class CellNeighborhoodCreator
{
public:
	CellNeighborhoodCreator() = default;
	CellNeighborhoodCreator(const RulePtr& rule);
	CellNeighborhoodCreator(const RulePtr& rule, CellRow* row);
	virtual ~CellNeighborhoodCreator() = default;
	
	CellNeighborhoodPtr createCellNeighborhood(const CellVector::const_iterator& center) const;
	virtual CellVector createCellNeighborhood2(const CellVector::const_iterator& center) const = 0;

	void setRow(CellRow* row) noexcept;
	const RulePtr& getRule() const noexcept;
	//Obsolete
	CellNeighborhoodCreatorPtr getPtrToCopy() const noexcept;
	//Better version of getPtrToCopy()
	virtual std::unique_ptr<CellNeighborhoodCreator> makeCopyFor(CellRow* row) const = 0;

	bool operator==(const CellNeighborhoodCreator& other) const noexcept;
	bool operator!=(const CellNeighborhoodCreator& other) const noexcept;

private:
	void throwIfRuleIsNullPtr() const;

	virtual CellNeighborhoodPtr doCreateCellNeighborhood(const CellVector::const_iterator& center) const = 0;
	virtual CellNeighborhoodCreatorPtr doGetPtrToCopy() const noexcept = 0;
	virtual bool equals(const CellNeighborhoodCreator& other) const noexcept;

protected:
	RulePtr _rule;
	CellRow* row_;
};

}
