#pragma once

#include <memory>
#include <vector>

namespace cellular_automata
{
//-----------------------------------------------------------------------------------------------
//FORWARD DECLARATIONS
class Cell;
class CellNeighborhood;
class Rule;
class KNearestNeighborsRule;
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
//POINTER ALIASES
using CellVector = std::vector<Cell>;

using CellNeighborhoodPtr = std::unique_ptr<CellNeighborhood>;

using RulePtr = std::shared_ptr<Rule>;
using KNearestNeighborsRulePtr = std::shared_ptr<KNearestNeighborsRule>;
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
//NAMESPACE INTEGERS
namespace integers
{
using state_t = long;
using integer_t = long;
}
//-----------------------------------------------------------------------------------------------

}
