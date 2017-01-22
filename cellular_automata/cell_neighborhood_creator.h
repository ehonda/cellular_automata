#pragma once

#include "type_definitions.h"

namespace cellular_automata
{

class CellNeighborhoodCreator
{
public:
	CellNeighborhoodCreator(const RulePtr& rule);
	virtual ~CellNeighborhoodCreator() = default;
	
	CellNeighborhoodPtr createCellNeighborhood(const CellVector::const_iterator& center) const;

	const RulePtr& getRule() const noexcept;
	CellNeighborhoodCreatorPtr getPtrToCopy() const noexcept;
	bool operator==(const CellNeighborhoodCreator& other) const noexcept;
	bool operator!=(const CellNeighborhoodCreator& other) const noexcept;

private:
	void throwIfRuleIsNullPtr() const;

	virtual CellNeighborhoodPtr doCreateCellNeighborhood(const CellVector::const_iterator& center) const = 0;
	virtual CellNeighborhoodCreatorPtr doGetPtrToCopy() const noexcept = 0;
	virtual bool equals(const CellNeighborhoodCreator& other) const noexcept;

protected:
	RulePtr _rule;
};

}
