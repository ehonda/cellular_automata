#pragma once

#include "type_definitions.h"

namespace cellular_automata {

class CellNeighborhoodCreator {
public:
	CellNeighborhoodCreator() = default;
	CellNeighborhoodCreator(const RulePtr& rule, CellRow* row);
	virtual ~CellNeighborhoodCreator() = default;
	
	virtual CellVector createCellNeighborhood(const CellVector::const_iterator& center) const = 0;

	void setRow(CellRow* row) noexcept;
	const RulePtr& getRule() const noexcept;

	virtual std::unique_ptr<CellNeighborhoodCreator> makeCopyFor(CellRow* row) const = 0;

	bool operator==(const CellNeighborhoodCreator& other) const noexcept;
	bool operator!=(const CellNeighborhoodCreator& other) const noexcept;

private:
	void throwIfRuleIsNullPtr() const;

	virtual bool equals(const CellNeighborhoodCreator& other) const noexcept;

protected:
	RulePtr rule_;
	CellRow* row_;
};

}
