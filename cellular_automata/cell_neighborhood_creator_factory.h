#pragma once

#include "type_definitions.h"

namespace cellular_automata {

class CellNeighborhoodCreatorFactory {
public:
	static CellNeighborhoodCreatorPtr getCreator(const RulePtr& rule, CellRow* row);

private:
	static void throwIfRuleIsNullPtr(const RulePtr& rule);
	static void throwIfCellRowIsNullPtr(CellRow* row);
};

}
