#pragma once

#include "type_definitions.h"

namespace cellular_automata {

class CellNeighborhoodCreator {
	friend class CellNeighborhoodCreatorFactory;

public:
	virtual ~CellNeighborhoodCreator() = default;
	
	virtual CellVector createCellNeighborhood(const CellVector::const_iterator& center) const = 0;

	void setRow(CellRow* row);
	const RulePtr& getRule() const noexcept;

	virtual std::unique_ptr<CellNeighborhoodCreator> makeCopyFor(CellRow* row) const = 0;

	bool operator==(const CellNeighborhoodCreator& other) const;
	bool operator!=(const CellNeighborhoodCreator& other) const;

private:
	void throwIfRuleIsNullPtr() const;

	virtual bool equals(const CellNeighborhoodCreator& other) const;

protected:
	CellNeighborhoodCreator() = default;
	CellNeighborhoodCreator(const RulePtr& rule, CellRow* row);

	RulePtr rule_;
	CellRow* row_;
};

}
