#pragma once

#include <memory>
#include <vector>

namespace cellular_automata
{
//-----------------------------------------------------------------------------------------------
//FORWARD DECLARATIONS
class BoundedCellRow;
class Cell;
class CellularAutomaton;
class CellNeighborhood;
class CellNeighborhoodCreator;
class CellRow;
class Rule;
class KNearestNeighborsRule;
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
//ALIASES
//Obsolete
using BoundedCellRowPtr = std::shared_ptr<BoundedCellRow>;
using CellularAutomatonPtr = std::shared_ptr<CellularAutomaton>;
using CellVector = std::vector<Cell>;
//Obsolete, CellNeighborhood is not used polymorphically
using CellNeighborhoodPtr = std::unique_ptr<CellNeighborhood>;
using CellNeighborhoodCreatorPtr = std::unique_ptr<CellNeighborhoodCreator>;
//Obsolete, not used polymorphically anymore
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
