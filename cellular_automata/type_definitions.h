#pragma once

#include <memory>
#include <vector>

namespace cellular_automata
{
//-----------------------------------------------------------------------------------------------
//FORWARD DECLARATIONS
class Cell;
class CellNeighborhood;
class CellNeighborhoodCreator;
class CellRow;
class Rule;
class KNearestNeighborsRule;
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
//ALIASES
using CellVector = std::vector<Cell>;
using CellNeighborhoodPtr = std::unique_ptr<CellNeighborhood>;
using CellNeighborhoodCreatorPtr = std::unique_ptr<CellNeighborhoodCreator>;
using CellRowPtr = std::shared_ptr<CellRow>;
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
