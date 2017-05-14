#pragma once

#include "type_definitions.h"

namespace cellular_automata {

class CellNeighborhoodCreatorFactory {
public:
	static CellNeighborhoodCreatorPtr getCreator(const RulePtr& rule, CellRow* row);

private:
	static void throwOnUnkonwnRuleType();
};

}
