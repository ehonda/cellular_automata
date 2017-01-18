#include "cell_neighborhood.h"

namespace cellular_automata
{

CellNeighborhoodPtr CellNeighborhood::createPtr(const CellVector& cells, const RulePtr& rule)
{
	return CellNeighborhoodPtr(new CellNeighborhood(cells, rule));
}

const integers::BaseBInteger& CellNeighborhood::getIntegerEncodedCellNeighborhood() const noexcept
{
	return _encodedCellNeighborhood;
}

bool CellNeighborhood::operator==(const CellNeighborhood& other) const noexcept
{
	return (_encodedCellNeighborhood == other._encodedCellNeighborhood) && (*_rule == *other._rule);
}

CellNeighborhood::CellNeighborhood(const CellVector& cells, const RulePtr& rule)
	: _rule(rule)
{
	encodeCellNeighborhood(cells);
}

void CellNeighborhood::encodeCellNeighborhood(const CellVector& cells)
{
	integers::BaseBInteger::BaseBRepresentation baseBRepresentation;
	for (const auto& cell : cells)
		baseBRepresentation.emplace_back(cell.getState());

	_encodedCellNeighborhood = integers::BaseBInteger(_rule->getNumberOfStates(), baseBRepresentation);
}

}
